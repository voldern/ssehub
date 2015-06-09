#include "SSEConfig.h" 
#include <glog/logging.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

/**
  Constructor.
*/
SSEConfig::SSEConfig(string file) {
  InitDefaults();
  load(file.c_str());
}

/**
  Initialize some sane default config values.
*/
void SSEConfig::InitDefaults() {

 ConfigKeys["server.bindip"]             = "0.0.0.0";
 ConfigKeys["server.port"]               = "8090";
 ConfigKeys["server.logdir"]             = "./";
 ConfigKeys["server.pingInterval"]       = "5";
 ConfigKeys["server.threadsPerChannel"]  = "5";


 ConfigKeys["amqp.host"]                 = "127.0.0.1";
 ConfigKeys["amqp.port"]                 = "5672";
 ConfigKeys["amqp.user"]                 = "guest";
 ConfigKeys["amqp.password"]             = "guest";
 ConfigKeys["amqp.exchange"]             = "amq.fanout";

}

/**
  Load a config file.
  @param file Filename of config to load. 
*/
bool SSEConfig::load(const char *file) {
    boost::property_tree::ptree pt;

    try {
      boost::property_tree::read_json(file, pt);
    } catch (...) {
      LOG(FATAL) << "Failed to parse config file.";
      return false;
    }  

    map<string, string>::iterator it;

    for (it = ConfigKeys.begin(); it != ConfigKeys.end();  it++) {
      try {
        string val = pt.get<std::string>(it->first);
        ConfigKeys[it->first] = val;
        DLOG(INFO) << it->first << " = " << ConfigKeys[it->first];
      } catch (...) {}
    }

  return true;
}

/**
  Fetch a config attribute and return as a string.
  @param key Config attribute to fetch. 
*/
const string &SSEConfig::GetValue(const string& key) {
  return ConfigKeys[key];
}

/**
  Fetch a config attribute and return as a int.
  @param key Config attribute to fetch. 
*/
int SSEConfig::GetValueInt(const string& key) {
  // FIXME: Probably better to use something else than atoi().
  return atoi(ConfigKeys[key].c_str());
}