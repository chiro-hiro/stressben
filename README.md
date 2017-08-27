# StressBen
This tool will give you abilities to test your rest API with highest concurrent.

# Installation
Clone source code from github:
```
~$ git clone https://github.com/tad88dev/stressben.git stressben
```
Build from source:
```
~$ cd stressben
~/stressben/$ make
~/stressben/$ sudo make install
```
# Usage
Create `queries.txt` which's containt URI.
```
/api/getBalance/address
/api/getHistory/address
```
Start stressben:
```
~$ stressben --host tradahacking.vn --user-agent ./data/useragent.txt --queries ./data/queries.txt
```

# License
This tool was distributed under [MIT License](https://github.com/tad88dev/stressben/blob/master/LICENSE)