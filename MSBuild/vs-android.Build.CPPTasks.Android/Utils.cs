// ***********************************************************************************************
// (c) 2012 Gavin Pugh http://www.gavpugh.com/ - Released under the open-source zlib license
// ***********************************************************************************************

// Misc pathing utils, and some constants.
 
using System;
using System.Diagnostics;
using System.Management;
using System.Text.RegularExpressions;

namespace vs_android.Build.CPPTasks.Android
{
	internal class Utils
	{
		public const int EST_MAX_CMDLINE_LEN = 16384;
		public const int EST_MAX_PATH_LEN = 256;

		public static string PathSanitize(string path)
		{
			path = path.Trim();

			// Remove quotes if it already has them. We'll re-add them if necessary.
			if ( path.Length > 1 )
			{
				if ( path.StartsWith( "\"" ) && path.EndsWith( "\"" ) )
				{
					path = path.Substring( 1, path.Length - 2 );
				}
			}

			// Quotes if path has spaces
			if ( ( path.IndexOf(' ') != -1 ) && ( path.IndexOf('\"') == -1 ) ) 
			{
				path = "\"" + path + "\"";
			}

			// Forward slashes please
			path = path.Replace('\\', '/');

			return path;
		}

		public static string PathFixSlashes(string path)
		{
			// Forward slashes please
			path = path.Trim();
			path = path.Replace('\\', '/');

			return path;
		}

		// Based on code from : http://social.msdn.microsoft.com/Forums/en-US/csharpgeneral/thread/d60f0793-cc92-48fb-b867-dd113dabcd5c
		public static void KillSpecificSubProcess(string exeName)
		{
			// UNTESTED!

			ManagementObjectSearcher searcher = new ManagementObjectSearcher("Select " + exeName + " From Win32_Process Where ParentProcessID=" + Process.GetCurrentProcess().Id);
			ManagementObjectCollection moc = searcher.Get();
			foreach (ManagementObject mo in moc)
			{
				int thisPid = Convert.ToInt32(mo["ProcessID"]);
				try
				{
					Process proc = Process.GetProcessById(thisPid);
					proc.Kill();
				}
				catch (ArgumentException)
				{

				}
			}
		}

		static readonly string REGEX_OPTIONAL_DRIVE_PREFIX = @"(?:[a-zA-Z]:)?";

		// Captures:
		//  foo.c
		//  C:\foo.c:
		static readonly string REGEX_PATH = @"(" + REGEX_OPTIONAL_DRIVE_PREFIX + "[^:]+)";

		enum MessageType
		{
			Warning,
			Error
		};

		/// <summary>
		/// Implements an error parser similar to the Eclipse error parser.
		/// </summary>
		struct ErrorParser
		{
			public Regex regex;
			public MessageType type;
			public int fileGroup;
			public int lineGroup;
			public int columnGroup;
			public string messageReplace;

			public string Parse(string input, string errorCode)
			{
				Match m = regex.Match(input);
				if (!m.Success)
					return null;

				string typeStr = type.ToString().ToLower();
				Debug.Assert(messageReplace != null); // parser must at least give a message

				string message = regex.Replace(input, messageReplace);

				Debug.Assert(fileGroup != 0);
				string path = PathFixSlashes(m.Groups[fileGroup].Value);

				if (lineGroup != 0)
				{
					string line = m.Groups[lineGroup].Value;

					if (columnGroup != 0)
					{
						string column = m.Groups[columnGroup].Value;

						// has file, has line, has column
						return string.Format("{0} ({1},{2}) : {3} {4}: {5}", path, line, column, typeStr, errorCode, message);
					}
					else
					{
						// has file, has line, no column
						return string.Format("{0} ({1}) : {2} {3}: {4}", path, line, typeStr, errorCode, message);
					}
				}
				else
				{
					// has file, no line, no column
					return string.Format("{0} : {1} {2}: {3}", path, typeStr, errorCode, message);
				}
			}
		};

		// Most aggressive (hardest) regex first. We short-circuit on the first match.
		private static readonly ErrorParser[] GnuCompilerParsers =
		{
			// foo.c:123:456: error: foo is bar
			new ErrorParser {
				regex = new Regex(@"^" + REGEX_PATH + @":(\d+):(\d+): error: (.*)$"),
				type = MessageType.Error,
				fileGroup = 1,
				lineGroup = 2,
				columnGroup = 3,
				messageReplace = "$4"
			},

			// foo.c:123:456: warning: foo is bar
			new ErrorParser {
				regex = new Regex(@"^" + REGEX_PATH + @":(\d+):(\d+): warning: (.*)$"),
				type = MessageType.Warning,
				fileGroup = 1,
				lineGroup = 2,
				columnGroup = 3,
				messageReplace = "$4"
			},

			// foo.c:123: error: foo is bar
			new ErrorParser {
				regex = new Regex(@"^" + REGEX_PATH + @":(\d+): error: (.*)$"),
				type = MessageType.Error,
				fileGroup = 1,
				lineGroup = 2,
				messageReplace = "$3"
			},

			// foo.c:123: warning: foo is bar
			new ErrorParser {
				regex = new Regex(@"^" + REGEX_PATH + @":(\d+): warning: (.*)$"),
				type = MessageType.Warning,
				fileGroup = 1,
				lineGroup = 2,
				messageReplace = "$3"
			}
		};

		private static readonly ErrorParser[] GnuLinkerParsers =
		{
			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + @":?\(\.\w+\+.*\): [Ww]arning: (.*)$"),
				type = MessageType.Warning,
				fileGroup = 1,
				messageReplace = "$2"
			},

			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + @":?\(\.\w+\+.*\): [Ee]rror: (.*)$"),
				type = MessageType.Error,
				fileGroup = 1,
				messageReplace = "$2"
			},

			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + @":(\d+): [Ww]arning: (.*)$"),
				type = MessageType.Warning,
				fileGroup = 1,
				lineGroup = 2,
				messageReplace = "$3"
			},

			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + @":(\d+): [Ee]rror: (.*)$"),
				type = MessageType.Error,
				fileGroup = 1,
				lineGroup = 2,
				messageReplace = "$3"
			},

			// Examples:
			// foo.o:bar.c:123: undefined reference to 'baz'
			// foo.o:bar.c:123: first defined here
			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + ":" + REGEX_PATH + @":(\d+): (.*)$"),
				type = MessageType.Error,
				fileGroup = 2,
				lineGroup = 3,
				messageReplace = "($1) $4"
			},

			// foo.o:bar.c:function construction vtable for CBaz: error: undefined reference ...
			new ErrorParser {
				regex = new Regex("^" + REGEX_PATH + ":" + REGEX_PATH + ":([^:]+): error: (.*)$"),
				type = MessageType.Error,
				// the file would be the object (since we don't get a relevant line in the source file anyway)
				fileGroup = 1,
				// Output would be:
				//
				// error: undefined reference ... (in bar.c:function construction vtable for CBaz)
				//
				messageReplace = "$4 (in $2:$3)"
			}
		};

		static string ParseMessage(ErrorParser[] parsers, string input, string errorCode)
		{
			foreach (var parser in parsers)
			{
				string output = parser.Parse(input, errorCode);
				if (output != null)
					return output + Environment.NewLine;
			}

			return input; // input did not match any parser, return as-is
		}

		public static string ParseCompilerMessage(string input)
		{
			return ParseMessage(GnuCompilerParsers, input, "CC");
		}

		public static string ParseLinkerMessage(string input)
		{
			return ParseMessage(GnuLinkerParsers, input, "LINK");
		}
	}
}