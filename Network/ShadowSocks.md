# ShadowSocks的原理

Shadowsocks 基于 Socks5协议 将代理服务器拆开成Server端和client端，然后通过以下方式进行通信：

![][1]

1. PC客户端（即你的电脑）发出请求基于Socks5协议跟SS-Local端进行通讯;
2. SS-Local和SS-Server两端通过多种可选的加密方法进行通讯;
3. SS-Server将收到的加密数据进行解密，还原初始请求，再发送到用户需要访问的服务网站，获取响应原路再返回到客户端。


# ShadowSocks 优点


# 扩展

为什么不应该用 SSL 翻墙？

SSL 设计目标:

1. 防内容篡改
2. 防冒充服务器身份
3. 加密通信内容

而翻墙的目标:

1. 不被检测出客户端在访问什么网站
2. 不被检测出服务器在提供翻墙服务

SSL 和这个目标还是有一些出入。其中最大的问题是，2. 防冒充服务器身份 这个功能多余了。他会导致墙嗅探出证书信息，继而墙会知道服务器身份。如果墙知道一个服务器身份是用来翻墙的，它要做的仅仅是封掉使用这个证书的所有 IP。

# 更多阅读

[翻墙路由器的原理与实现](http://drops.wooyun.org/papers/10177)
[翻墙软件的选择与安全系数](https://plus.google.com/+GhostAssassin/posts/TtWFAQmSMVE)
[关于翻墙和匿名与网络安全类科普文大集合](https://plus.google.com/+GhostAssassin/posts/a8aKzvZLsuV)


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Network_ShadowSocks_1.png


