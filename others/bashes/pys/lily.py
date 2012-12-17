#!/usr/bin/env python
# encoding: utf-8
"""
lily.py

Created by Yo_oY on 2011-11-28.
Copyright (c) 2011 __MyCompanyName__. All rights reserved.
"""

import urllib
import httplib2
import random


def main():    
    http = httplib2.Http()
         
    baseurl = 'http://bbs.nju.edu.cn'
    #userdir是随机生成每个用户的线程，随意指派好像也可以
    userdir = '/vd'+"%0d"%random.randint(0,100000)
    logapp = '/bbslogin?type=2'
    
    headers = {
        'Host': 'bbs.nju.edu.cn',
        'Connection': 'keep-alive',
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.2 (KHTML,like Gecko) Chrome/15.0.874.121 Safari/535.2',
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Encoding': 'gzip,deflate,sdch',
        'Accept-Language': 'zh-CN,zh;q=0.8',
        'Accept-Charset': 'GBK,utf-8;q=0.7,*;q=0.3',
    }
    
    
    url = baseurl + userdir + logapp
    body = {'id':'mtawaken','pw':'08gyjgcs33','lasturl':'bbs.nju.edu.cn/bbsmain'}
    response, content = http.request(url, 'POST', headers=headers, body=urllib.urlencode(body))
    
    #百合是在返回的content里面用js写cookie的，而不是在response里用setCookie，所以要对返回的content进行解析
    start = content.find("('") + 2
    end = content.find("')")
    cookies = content[start:end]
    
    split_1 = cookies.find('N')
    split_2 = cookies.find('+')
    
    #cookie总共有四项，分别是 _U_NUM _U_UID _U_KEY FOOTKEY，其中FOOTKEY好像是可以为空或者随意指派的
    _U_NUM = int(cookies[0:split_1])
    _U_UID = cookies[split_1 + 1:split_2]
    _U_KEY = int(cookies[split_2 + 1:])
    
    #这里要注意对_U_NUM+2，对_U_KEY-2，不知道百合这么设计是因为什么，之前就因为这个错误卡了很久
    cookie = "_U_NUM=%d; _U_UID=%s; _U_KEY=%d; FOOTKEY=%d"%(_U_NUM + 2, _U_UID
, _U_KEY - 2, 1322546045)
    headers['Cookie'] = cookie
    #以下的header不一定需要
    headers['Referer'] = baseurl + userdir + '/bbspst?board=test'
    #headers['Content-Length'] = '61'
    headers['Cache-Control'] = 'max-age=0'
    headers['Origin'] = baseurl

    #以下是在test版测试发帖
    postpage = '/bbssnd?board=test'
    body = {'title':'test',
            'pid':'0',
            'reid':'0',
            'signature':'1',
            'autocr':'on',
            'text':'testbed',
            }
    url = baseurl + userdir + postpage
    
    response, content = http.request(url, 'POST', headers=headers, body=urllib.urlencode(body))
    
    print response
    print content


if __name__ == '__main__':
    main()

