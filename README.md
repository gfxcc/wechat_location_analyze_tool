# analyze tool for wechat data


## Build

### Require
**Boost**  
	Find detail at [Boost](http://www.boost.org)

```
wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar -xvf boost_1_64_0.tar.gz
cd boost_1_64_0
sudo cp -r boost /usr/local/include/
```

**JSON for Modern C++**

Find dtail at [JSON](https://github.com/nlohmann/json)   

```
wget https://github.com/nlohmann/json/releases/download/v2.1.1/json.hpp
sudo cp json.hpp /usr/local/include/
```

**Clang++**
if you want use `g++`, please modify `Makefile`
```
# CC = clang++
CC = g++ 
```

### Start build project
**Build Project**  

```
cd path_of_project  
make
```

## Usage

```
Usage: analyze [OPTION] pattern
       -r arg: set path_region
       -w arg: set path_wechat
       -o arg: enable output to file and set path_output
       -l arg: row_need_read_from_wechat
       -d    : enable debug mode
       -h    : help
```

## Data format
...

## Output Simple


```
-------------------------Statistic Result---------------------------
10001 wechat account exist
Matched:2598 ( 25%  )
Single:1784 ( 17%  ) 单一地址
Double:487 ( 4%  ) 两个地址
Multi:327 ( 3%  ) 多个地址

name:香妃果宴
intro:新疆特产：葡萄干、若羌大枣、和田大枣、巴旦木、纸皮核桃、无花果、精河枸杞、木垒鹰嘴豆、昆仑山胎菊、大漠肉苁蓉、伊犁薰衣草。绿色、天然、健康。
香妃果�
妃果宴
果宴
宴
4 regions matched successed
652722:精河县
653221:和田县
653201:和田市
652824:若羌县
---------------------------------------------------
name:深圳市天杰汽车用品有限公司
intro:善领汽电集团旗下专门负责4S店集团及特殊渠道运营的销售服务公司，代理众易畅、任我通、艾酷等多个知名品牌，经营项目：DVD导航、大屏机、原车屏升级、360全景、智能云镜、记录仪、脚踏板、行李架、前后大包围、电动踏板、电动尾门；美容镀晶等
深圳市�
圳市天�
市天杰�
天杰汽�
杰汽车�
汽车用�
车用品�
用品有�
品有限�
有限公�
限公司
公司
司
1 regions matched successed
440300:深圳市
---------------------------------------------------
name:南昌田尾香城园度假生态游
intro:【田尾香城园度假村】■座落于:南昌后花园湾里洗药湖登山起点处■农活体验:耕田插秧、种菜锄地、挖红暑、做豆腐、磨米粉做米谷、做菜饼、砍柴做大锅饭■娱乐项目:骑马射击、台球乒乓球、烧烤烤红署、垂钓打猎、植树、KTV电影院、抓鸡、现场烤窑鸡
南昌田�
昌田尾�
田尾香�
尾香城�
香城园�
城园度�
园度假�
度假生�
假生态�
生态游
态游
游
2 regions matched successed
360121:南昌县
360100:南昌市
---------------------------------------------------
