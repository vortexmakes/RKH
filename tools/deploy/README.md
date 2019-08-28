# How to release
```bash 
cd path/to/<release-dir>
vim changelog   # Copy the latest changes from <rkh-dir>
cd path/to/<rkh-dir>/tools/deploy
./rkh-deploy.sh clean path/to/<release-dir>
./rkh-deploy.sh deploy 3.2.3 ../../../rkh-git/ path/to/<release-dir>    # Use an absolut path
./rkh-release.sh -v 3.2.3 -r vortexmakes/RKH -s path/to/<release-dir>/rkh_v3.2.3.tar.gz -m path/to/<release-dir>/changelog -t <token>
```
