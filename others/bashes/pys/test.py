#!/usr/bin/env python
#encoding:utf-8
import requests
import random
baseurl = 'http://bbs.nju.edu.cn'
userdir = '/vd'+'%0d'%random.randint(0,100000)
logapp = '/bbslogin?type=2'
headers = {
     'Host': 'bbs.nju.edu.cn',
     'Connection': 'keep-alive',
     'User-Agent': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.2 (KHTML    ,like Gecko) Chrome/15.0.874.121 Safari/535.2',
     'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*    ;q=0.8',
     'Accept-Encoding': 'gzip,deflate,sdch',
     'Accept-Language': 'zh-CN,zh;q=0.8',
     'Accept-Charset': 'GBK,utf-8;q=0.7,*;q=0.3',
}
url = baseurl + userdir + logapp
body = {'id':'mtawaken','pw':'08gyjgcs33','lasturl':'bbs.nju.edu.cn/bbsmain'}
response = requests.post(url,params=body,headers=headers) 
#set cookies
content = response.text
strIdentify = "setCookie"
start = content.find(strIdentify)+len(strIdentify)+2
content = content[start:]
end = content.find("'")
content = content[:end]
split_1 = content.find('N')
split_2 = content.find('+')

_U_NUM = int(content[0:split_1])
_U_UID = content[split_1+1:split_2]
_U_KEY = int(content[split_2+1:])

cookie = "_U_NUM=%d; _U_UID=%s; _U_KEY=%d; FOOTKEY=%d" % (_U_NUM+2,_U_UID,_U_KEY-2,1322546045)
headers['Cookie'] = cookie
'''
postpage = '/bbssnd?board=test'
body = {
'title':'ttt',
'pid':'0',
'reid':'0',
'signature':'1',
'autocr':'on',
'text':'12345',
}
url = baseurl + userdir+postpage
content = requests.post(url,params=body,headers=headers)
print content.text
'''
headers['Content-Type'] = 'multipart/form-data'
postpage = '/bbsdoupload'
#headers['Referer'] = baseurl + userdir+'/bbsupload?ptest=text&board=test'
url = baseurl + userdir+postpage
payload={'up':'2012.jpg','exp':'','ptext':'text','board':'test'}
files = {'file':open('/home/mtawaken/123.jpg','rb')}
content = requests.post(url,data=payload,files=files)
print content.content
