# How to deploy and release

## Create a release directory
```bash 
mkdir path/to/<release-dir>
```

## Clone RKH framework
```bash 
cd path/to/<projects>
git clone https://github.com/vortexmakes/RKH.git
```

## Add changes to changelog file
```bash 
cd path/to/<projects>/RKH           # RKH clone
vim tools/deploy/changelog.json     # Add a new release section and complete 
                                    # it with your changes. Do not forget to 
                                    # add the release version and the release 
                                    # date 
```

## Set environment variables
```bash 
export RKH_FTP_SERVER=...
export RKH_FTP_USR=...
export RKH_FTP_PASSW=...
```

## Execute release process
```bash 
cd path/to/<projects>/RKH           # RKH clone
cd tools/deploy
./deploy.py -c <release-version> vortexmakes/RKH <path/to/<release-dir> <github-token>
./deploy.py <release-version> vortexmakes/RKH <path/to/<release-dir> <github-token>
```
