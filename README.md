# analyze tool for wechat data

This tools used to analyze region information from indicated format wechat 
data.   
[clean data]->[parse data]->[organize data]->[analyze region info]->[statistic]->[json ouput]
Region information analyzation rely on [CRK](https://github.com/gfxcc/crk)

## Build

### Start build project
**Build Project**  

```
git clone https://github.com/gfxcc/wechat_location_analyze_tool.git
cd wechat_location_analyze_tool
mkdir build; cd build
cmake ..
make
```

## Usage

```
Usage: analyze [OPTION] pattern
       -w arg: set path_wechat
       -o arg: enable output to file and set path_output
       -l arg: row_need_read_from_wechat
       -d    : enable debug mode
       -h    : help
```

## Sample output
```
{
  "WechatAccount": [
{
  "date": "2016-09-18",
  "field_5": "http://mp.weixin.qq.com/mp/qrcode?scene=10000004&size=102&__biz=MzI4MTQ2NjE4MQ==",
  "filed_0": "4634689",
  "filed_3": "",
  "filed_6": "1474128002",
  "intro": "满市城投公司",
  "name": "满洲里市城发投集团",
  "regions": {
    "150781": "满洲里市"
  },
  "uuid": "MzI4MTQ2NjE4MQ=="
},
{
  "date": "2016-09-18",
  "field_5": "http://mp.weixin.qq.com/mp/qrcode?scene=10000004&size=102&__biz=MzI1MDQ2NDgxOA==",
  "filed_0": "4634691",
  "filed_3": "ksxcfc",
  "filed_6": "1474128005",
  "intro": "玉山城西主流商品房，别墅二手交易",
  "name": "昆山小崔房产",
  "regions": {
    "320583": "昆山市",
    "410603": "山城区"
  },
  "uuid": "MzI1MDQ2NDgxOA=="
},
{
  "date": "2016-09-18",
  "field_5": "http://mp.weixin.qq.com/mp/qrcode?scene=10000004&size=102&__biz=MzIxODU3ODU2OQ==",
  "filed_0": "4634700",
  "filed_3": "jjukaoyanzhijia",
  "filed_6": "1474128035",
  "intro": "我们是九江学院专门为考研服务的一个校级社团！我们全心全意为九江学院的考研做服务。",
  "name": "九院考研之家",
  "regions": {
    "360400": "九江市",
    "360421": "九江县"
  },
  "uuid": "MzIxODU3ODU2OQ=="
},
{
  "date": "2016-09-18",
  "field_5": "http://mp.weixin.qq.com/mp/qrcode?scene=10000004&size=102&__biz=MzIxODU4MjE0Mg==",
  "filed_0": "4634710",
  "filed_3": "musuzhou",
  "filed_6": "1474128104",
  "intro": "欢迎大家",
  "name": "MU苏州",
  "regions": {
    "320500": "苏州市"
  },
  "uuid": "MzIxODU4MjE0Mg=="
},
.
.
.
```
