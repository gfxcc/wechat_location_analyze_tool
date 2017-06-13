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
