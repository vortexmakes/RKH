# How to release
```bash 
cd path/to/release
vim changelog   # Copy the latest changes from <rkh-dir>/README.md 
                # "RKH Release notes"
cd path/to/<rkh-dir>/tools/deploy
./rkh-deploy.sh clean path/to/release
./rkh-deploy.sh deploy 3.2.3 ../../../RKH/ path/to/release # Use an absolut path
./rkh-release.sh -v 3.2.3 -r vortexmakes/RKH -s path/to/release/rkh_v3.2.3.tar.gz -m path/to/release/changelog -t <token>
```
