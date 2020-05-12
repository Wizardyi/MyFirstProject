/*
 * =====================================================================================
 *
 *       Filename:  strings.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2010年06月07日 10时20分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jim (xcwen), jim@taomee.com
 *        Company:  taomee
 *
 * =====================================================================================
 */

#ifndef  strings_INC
#define  strings_INC
#include <string>
#include <algorithm>
#include <fstream>
#include <stdint.h>
#include <libtaomee++/utils/md5.h>
#include <libtaomee++/utils/tcpip.h>
#include <string.h>

inline bool isnewline(const char c)
{
    return c == '\r' || c == '\n';
}

// Make sure that we can use Mac, DOS, or Unix style text files on any system
// and they will work, by making sure the definition of whitespace is consistent
inline bool portable_isspace(const char c)
{
    // returns true only on ASCII spaces
    if (static_cast<unsigned char>(c) >= 128)
        return false;
    return isnewline(c) || isspace(c);
}

// Make sure we regard '\r' and '\n' as a space, since Mac, Unix, and DOS
// all consider these differently.
inline bool notspace(const char c)
{
    return !portable_isspace(c);
}

enum { REMOVE_EMPTY = 0x01, /**< REMOVE_EMPTY : remove empty elements. */
	  STRIP_SPACES  = 0x02  /**< STRIP_SPACES : strips leading and trailing blank spaces. */
};
inline std::string &strip(std::string &str)
{
	// If all the string contains is whitespace,
	// then the whitespace may have meaning, so don't strip it
	std::string::iterator it = std::find_if(str.begin(), str.end(), notspace);
	if (it == str.end())
		return str;

	str.erase(str.begin(), it);
	str.erase(std::find_if(str.rbegin(), str.rend(), notspace).base(), str.end());

	return str;
}

#include <vector>
inline std::vector< std::string > split(std::string const &val, char c=',', int flags=REMOVE_EMPTY|STRIP_SPACES)
{
	std::vector< std::string > res;
	std::string::const_iterator i1 = val.begin();
	std::string::const_iterator i2 = val.begin();
	//std::string val1("");
	//printf("===val[%d]===",val1.begin() ==val1.end());

	while (i2 != val.end()) {
		if (*i2 == c) {
			std::string new_val(i1, i2);
			if (flags & STRIP_SPACES)
				strip(new_val);
			if (!(flags & REMOVE_EMPTY) || !new_val.empty())
				res.push_back(new_val);
			++i2;
			if (flags & STRIP_SPACES) {
				while (i2 != val.end() && *i2 == ' ')
					++i2;
			}

			i1 = i2;
		} else {
			++i2;
		}
	}

	std::string new_val(i1, i2);
	if (flags & STRIP_SPACES)
		strip(new_val);
	if (!(flags & REMOVE_EMPTY) || !new_val.empty()){
		res.push_back(new_val);
	}
	return res;
}

//当dst传入null时将会使用 static buf,最大长度是500
inline char * bin2hex(char * dst, char * src,int len,int max_len=0xFFFF)
{
	static char buf[500*3+1];
	if (dst==NULL){
		max_len=500;
		dst=buf;
	}

	int hex;
	int i;
	int di;
	if (len>max_len) len=max_len;
	for(i=0;i<len;i++){
		hex=((unsigned char)src[i])>>4;
		di=i*3;
		dst[di]=hex<10?'0'+hex:'A'-10 +hex ;
		hex=((unsigned char)src[i])&0x0F;
		dst[di+1]=hex<10?'0'+hex:'A'-10 +hex ;
		dst[di+2]=' ';
	}
	dst[len*3]=0;
	return dst;
}

//dst为NULL时，会使用static char buf[500*2+1]; ,最多500个字节
//   不为：NULL，由使用用户传进来的buf
//is_upper:是否用大写字母:0不是， !=0:是
inline void bin2hex_frm(char * dst, char * src,int len,  int is_upper  )
{
	uint32_t max_len=len; 
	static char buf[500*2+1];
	if (dst==NULL){
		max_len=500;
		dst=buf;
	}
	char ch_a;	
	if (is_upper!=0 ){
		ch_a='A';
	}else{
		ch_a='a';
	}

	int hex;
	int i;
	int di;
	if (len>max_len) len=max_len;
	for(i=0;i<len;i++){
		di=i*2;
		hex=((unsigned char)src[i])>>4;
		dst[di]=hex<10?'0'+hex:ch_a-10 +hex ;
		hex=((unsigned char)src[i])&0x0F;
		dst[di+1]=hex<10?'0'+hex:ch_a-10 +hex ;
	}
	dst[len*2]=0;
}

inline int get_hex(char ch)
{
	if (ch>='0' && ch<='9') return  ch-'0';
	else if (ch>='A' && ch<='F') return  10+ch-'A';
	else if (ch>='a' && ch<='f') return  10+ch-'a';
	else return 0; 
}

inline void hex2bin(char * dst, const char * src,int len)
{
	for(int i=0;i<len;i++){
		dst[i]=(unsigned char)((get_hex(src[i*2])<<4)+get_hex(src[i*2+1]));
	}
}

#ifndef NOUSE_VERSION_STR   
#include <libtaomee++/utils/version_str.hpp>
#endif

#endif
