using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using static System.Console;

int LineLength = 4094;
const int LinesCount = 128 * 1024;
const string InputFilename = "input.data";
const string Alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
var random = new Random();

IEnumerable<string> GenerateLines()
    => Enumerable.Range(1, LinesCount).Select(_ => 
            new string(Enumerable.Range(1, LineLength).Select(_ 
                => Alphabet[random.Next(0, Alphabet.Length)]).ToArray())
    );

using var sr = new StreamWriter(new FileStream(InputFilename, FileMode.Create, FileAccess.Write, FileShare.Read));
foreach (var line in GenerateLines())
    sr.WriteLine(line);