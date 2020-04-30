#ifndef SHARE_UTILITY_H
#define SHARE_UTILITY_H

#include <algorithm>

class ShareUtility
{
	public:
		  // 字符串输入 特殊字段判断
		  static bool CheckIllegalString(const std::string& strName) 
		  {
		      auto itor = std::find_if(strName.begin(), strName.end(), ::iscntrl);
		      if (itor != strName.end()) {
         		 return false;
		      }
      		itor = std::find_if(strName.begin(), strName.end(), ::isspace);
      		if (itor != strName.end()) {
      		    return false;
     		 }
      		itor = std::find_if(strName.begin(), strName.end(), ::ispunct);
		    if (itor != strName.end()) {
        	    return false;
	         }
    	     return true;
	 		}
        	
};


#endif
