using System.Xml.Linq;

namespace ConvertMatrix
{
  struct NameBlock
  {
    public string Name="";
    public int Id = 0;
    public int Kod = 0;
    public string FromWhom = "";
    public NameBlock(string s) 
    {
      var _s0 = s.Split(" ");
      try
      {
        Id = Convert.ToInt32(_s0[1]);
        Name = _s0[2].Replace(":","");
        Kod = Convert.ToInt32(_s0[3]);
        FromWhom = _s0[4];
      }
      catch (Exception)
      {
        Id = -1;
        Name = "";
        Kod = -1;
        FromWhom = "";
      }
    }
  }

  struct Element
  {
    public string Name;
    public Element(string s)
    {
      s = s.Replace("\"", "'");
      var _s0 = s.Split(":");
      Name = _s0[0].Split(" ")[2].Trim();
      var _s1 = _s0[1].Split(" ").Where(x=>x.Length>0).ToArray();
      
      var Name1=_s1[1];
    }
  }
  struct NameBlockElement
  {
    public NameBlock NameBlock; 
    public List<Element> Elements;

    public NameBlockElement(List<string> ls)
    {
      Elements = new List<Element>();
      NameBlock = new NameBlock(ls.ElementAt(0));
      for (int i = 1; i < ls.Count; i++)
        Elements.Add(new Element(ls[i]));
    }
  }
  public class CanConvert
  {
    #region data
    private readonly string _pathFileSources;
    private readonly string _path;
    private readonly string _fileName;
    private Dictionary<int, List<string>> mls = new();
    private Dictionary<int, NameBlockElement> dBlock = new();
    #endregion
    public CanConvert(string pathSources)
    {
      _pathFileSources = pathSources;
      //      _path = Path.GetDirectoryName(_pathFileSources);
      _path = "";

      _fileName = Path.GetFileNameWithoutExtension(_pathFileSources);

      ReadFile();
      StrToDict();
      //string extension = Path.GetExtension(_pathFileSources); //string _fileName = Path.GetFileName(_pathFileSources);

    }

    #region core
    public void ReadFile(string pathFile="")
    {
      StringComparison comp = StringComparison.Ordinal;
//      Console.WriteLine("   {0:G}: {1}", comp, s.Contains(sub1, comp));
      string _pathFile = string.IsNullOrEmpty(pathFile)? _pathFileSources : pathFile;
      List<string> ls=new();
      if (File.Exists(_pathFile))
        ls = File.ReadAllLines(_pathFile).ToList();

      bool _isDan = false;
      List<string> _ls0 = new();
      //Dictionary<int, List<string>> mls = new();
      int _k = -1;
      foreach (var it in ls)
      {
        if (it.Length > 0 && (it.Substring(0, 3).ToLower() == "bo_"))
        { 
          _isDan = true;
          _k++;
          _ls0 = new();
        }
        if (_isDan)
          _ls0.Add(it);
        if (it.Length == 0 && _isDan)
        {
          mls.Add(_k, _ls0);
          _isDan = false; 
        }
        if (it.Length == 0)
          _isDan = false;
      }
    }

    public void StrToDict()
    {
      foreach (var it in mls)
      {
        NameBlockElement _nbe = new NameBlockElement(it.Value);
        dBlock.Add(_nbe.NameBlock.Id, _nbe);
      }
    }

    #endregion
  }
}