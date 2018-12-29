# note
  - 该网络库是一套基于`berkeley socket api`封装的一个简易网络库，接口少而且直观，使用简单，调用方便。头文件只有一个network.h，api数量只有5个，却包含了udp，tcp client 和tcp server三种网络模型。
  - 网络库已经在Ubuntu16.04.5 X86-64系统上验证通过。
  - 可以通过修改`NETWORK_API`的宏定义中的前缀，来实现修改api的接口声明，便于适用不同的模块，不同的企业。
  - 该网络库是基于linux系统的，用户可以通过修改相关头文件很方便的移植到其它系统，比如win，或者嵌入式平台。如果是嵌入式平台，必须支持标准socket api。
  - 库中包含udp，tcp client， tcp server三种网络demo。使用时请根据实际的网络情况，修改demo中的ip和port。

# quick start
  我们以linux系统为例，介绍一下使用和测试方法。

	sudo apt-get install cmake
	cd network
	mkdir build 
	cd build
	cmake ..
	make
	./bin/netdemo

# LICENSE
  本网络库开放源码并遵循 [The MIT License](LICENSE) 开源协议。
