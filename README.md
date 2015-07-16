What is ZelBit
ZelBit (ZLB) is the worlds first... With other innovations including a double-life instead of a half-life.

License

ZelBit is released under the terms of the MIT license. See COPYING for more information or see http://opensource.org/licenses/MIT.

Building for Linux

From Terminal

$sudo apt-get update && sudo apt-get upgrade

$sudo apt-get install build-essential libboost-all-dev libcurl4-openssl-dev libdb5.1-dev libdb5.1++-dev git qt-sdk libminiupnpc-dev

$sudo apt-get remove qt5-default qttools5-dev-tools && sudo apt-get autoremove && sudo apt-get clean && sudo apt-get autoclean

$git clone https://github.com/zelbit/zelbit.git

$ cd /zelbit

$qmake "USE_UPNP=-"

$make

