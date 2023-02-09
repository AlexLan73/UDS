using System;

namespace ConvertMatrix // Note: actual namespace depends on the project name.
{
  public class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("Hello World!");
      if (args.Length > 0)
      { 
        var _canConvert = new CanConvert(args[0]); 
      }

    }
  }
}