What is ZelBit
----------------
ZelBit (ZLB) is the worlds first silver backed cryptocurrency. ZelBit uses Scrypt as a proof-of-work algorithm and has other innovations.
 - Block Time: 3 Minutes
 - Difficulty Retarget: 3 Days
 - Block Reward: 0.1 doubling every 43824 block
 - Total Coins: 27 million

License
----------------
ZelBit is released under the terms of the MIT license. See COPYING for more information or see http://opensource.org/licenses/MIT.

Development process
-------------------
Developers work in their own trees, then submit pull requests when they think their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the ZelBit development team members simply pulls it.

If it is a more complicated or potentially controversial change, then the patch submitter will be contacted by one of ZelBit's development team. 

The patch will be accepted if there is broad consensus that it is a good thing. Developers should expect to rework and resubmit patches if the code doesn't match the project's coding conventions (see doc/coding.txt) or are controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/zelbit/zelbit/tags) are created
regularly to indicate new official, stable release versions of ZelBit.

Building ZelBit on Linux from terminal
----------------
      $sudo apt-get update && sudo apt-get upgrade

      $sudo apt-get install build-essential libboost-all-dev libcurl4-openssl-dev libdb5.1-dev libdb5.1++-dev git qt-sdk libminiupnpc-dev

      $sudo apt-get remove qt5-default qttools5-dev-tools && sudo apt-get autoremove && sudo apt-get clean && sudo apt-get autoclean

      $git clone https://github.com/zelbit/zelbit.git

      $ cd /zelbit

      $qmake "USE_UPNP=-"

      $make

