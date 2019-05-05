#include "log.hpp"
#include "exception.hpp"

#include "fstream"

//Private
Log::Log(): filename("log.log"){ }

void Log::Add(typed_string message, LOGTYPE type){
  std::ofstream file(this->filename.c_str(), std::ios_base::app);
  if (!file.is_open() || file.fail()) throw Exception("Failed to open file");

  switch(type){
    case ERROR:
      file << "Error: ";
      break;
    case DEBUG:
      file << "Debug: ";
      break;
  }
  file << message << std::endl;
  file.close();
  if (file.fail()) throw Exception("Failed to close file");
}

//Public

//Getters

/*static*/ Log& Log::GetInstance(){
  static Log instance;
  return instance;
}

const typed_string& Log::GetFilename() const{
  return this->filename;
}

typed_string Log::Last(){
  std::ifstream file(this->filename.c_str());
  if (!file.is_open() || file.fail()) throw Exception("Failed to open file");

  typed_string result;
  getline(file, result);
  if (file.fail() && !file.eof()) throw Exception("Failed to read data from file");
  file.clear();
  
  file.close();
  if (file.fail()) throw Exception("Failed to close file");

  return result;
}

//Setters

void Log::SetFilename(typed_string& name){
  this->filename = name;
}