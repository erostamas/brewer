class Utils{
public:
    static bool fileExists (const std::string& name) {
      struct stat buffer;   
      return (stat (name.c_str(), &buffer) == 0); 
    }

    static const std::vector<std::string> split(const std::string& s, const char& c)
    {
        std::string buff{""};
        std::vector<std::string> v;
        
        for(auto n:s)
        {
            if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
        }
        if(buff != "") v.push_back(buff);
        
        return v;
    }
};