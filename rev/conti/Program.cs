using System;
using System.IO;
using Org.BouncyCastle.Crypto.Engines;
using Org.BouncyCastle.Crypto.Parameters;
using System.IO.Compression;

namespace Conti
{
    class Program
    {
        static void FileEnumeration(string dir, List<FileInfo> files)
        {
            foreach (string file in Directory.GetFiles(dir, "*.*", SearchOption.TopDirectoryOnly))
            {
                files.Add(new FileInfo(file));
            }
            foreach (string subDir in Directory.GetDirectories(dir))
            {
                try
                {
                    FileEnumeration(subDir, files);
                }
                catch (UnauthorizedAccessException ex) { }
            }
        }

        static void Encrypt(string filename)
        {
            Random rnd = new Random(1337);
            byte[] keyBytes = new byte[32];
            byte[] IVbytes = new byte[12];
            rnd.NextBytes(keyBytes);
            rnd.NextBytes(IVbytes);
            byte[] plain = System.IO.File.ReadAllBytes(filename);
            byte[] enc = new byte[plain.Length];
            var cipher = new ChaCha7539Engine();
            cipher.Init(true, new ParametersWithIV(new KeyParameter(keyBytes), IVbytes));
            cipher.ProcessBytes(plain, 0, plain.Length, enc, 0);
            string myDir = Path.GetDirectoryName(filename) + "\\encrypted\\";
            if (!Directory.Exists(myDir))
            {
                Directory.CreateDirectory(myDir);
            }
            var encFilename = myDir + Path.GetFileName(filename).Replace(Path.GetExtension(filename), ".EXTEN");
            System.IO.File.WriteAllBytes(encFilename, enc);
        }

        static void Main()
        {
            List<FileInfo> filesToEncrypt = new List<FileInfo>();
            FileEnumeration("encryptThese", filesToEncrypt);
            foreach (FileInfo file in filesToEncrypt)
            {
                //Encrypt(file.FullName);
            }
            ZipFile.CreateFromDirectory("encryptThese\\encrypted", "encryptedFiles.zip");
        }
    }
}