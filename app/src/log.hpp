#ifndef LOG_HPP
#define LOG_HPP

#include "type.hpp"

class Log{
  private:
    //Members
    enum LOGTYPE{ ERROR, DEBUG };
    typed_string filename;
    //Methods
    Log();
    Log(const Log& log);
    void operator=(const Log& log);
    void Add(typed_string error, LOGTYPE type);
  public:
    //Getters
    static Log& GetInstance();
    const typed_string& GetFilename() const;
    typed_string Last();
    //Setters
    void SetFilename(typed_string& name);
    //Template definitions
    template <class type>
    void Error(const type& msg){
      typed_stringstream errorStr;
      errorStr << msg;
      this->Add(errorStr.str(), ERROR);
    }
    template <class type>
    void Debug(const type& msg){
      typed_stringstream debugStr;
      debugStr << msg;
      this->Add(debugStr.str(), DEBUG);
    }
};

#endif