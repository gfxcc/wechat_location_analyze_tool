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

**Build Project**  

```
cd path_of_project  
make
```

## Usage

```
analyze // run default path_of_wechat_file
analyze path_of_wechat_file  // specific path
```

## Data format
...
