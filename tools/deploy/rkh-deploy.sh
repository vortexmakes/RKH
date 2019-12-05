# !/bin/bash -e
#

outdir_path=$2
outdir_prefix="rkh_v"
format="zip"
outfile=$outdir_prefix"$outdir_path""."$format
outdir_name=$outdir_path"/"$outfile
argVersion=$(echo ${2%/})
argWorkDir=$(echo ${3%/})
argOutDir=$(echo ${4%/})
res=0

usage() {
    echo "Creates artifacts in order to be released"
    echo "Usage:"
    echo "    rkh-deploy.sh deploy <release-version> <working-dir-path> <output-dir-path>"
    echo "    rkh-deploy.sh clean <output-dir-path>"
    echo ""
    echo "Warning:"
    echo "    Use an absolute path for <output-dir-path> argument"
    echo ""
    echo "Example:"
    echo "    path/to/rkh/tools/deploy$ ./rkh-deploy.sh deploy 1.0 ../../../rkh-git/ ~/out/"
}

check_repo() {
    curr_dir=$PWD
    cd $1
    if [ -d .git ]; then
        git remote -v | grep origin | grep "RKH.git" | grep -q "(fetch)"
        if [ ! $? ]; then
            echo "[ERROR] <working-dir-path> ($1) is not a RKH repository"
            res=1
        else
            branch=$(git branch | grep "*\s" | awk '{print $2}')
            if [ $branch == "master" ]; then
                git status
                res=0
            else
                echo "[WARNING] It has to be realeased only from master branch"
                res=0
            fi
        fi
    else
        echo "[ERROR] <working-dir-path> ($1) is not a RKH repository"
        res=1
    fi
}

check_version() {
    version=$(grep "RKH_VERSION_CODE" source/fwk/inc/rkhfwk_version.h | awk '{print $3}')
    version=$(echo $version | sed -e 's/0x\(.*\)u/\1/')
    major=$(echo $version | sed -e 's/\([0-9]\{1\}\)[0-9]\{3\}/\1/')
    minor=$(echo $version | sed -e 's/.\([0-9]\{1\}\)[0-9]\{2\}/\1/')
    patch=$(echo $version | sed -e 's/..\([0-9]\{1\}\)/\1/')
    #patch=$(echo $version | sed -e 's/\([0-9]\{2\}\{1\}\)/\1/')
    echo "Code version:    v"$major"."$minor"."$patch
    echo "Release version: v"$argVersion
}

case "$1" in
	deploy)
        echo
        echo "Verifying directories and files"
        echo "-------------------------------"
        if [ -z $2 ]; then
            echo "[ERROR] Please, supply a valid release version number"
            exit 1
        fi
        if [ -z $argWorkDir -o ! -d $argWorkDir ]; then
            echo "[ERROR] Please, supply a valid working directory"
            exit 1
        fi
        if [ -z $argOutDir -o ! -d $argOutDir ]; then
            echo "[ERROR] Please, supply a valid deploy output directory"
            exit 1
        fi
        check_repo $argWorkDir
        if [ $res = 1 ]; then
            exit 1
        fi
        if [ ! -d doc ]; then
            echo "[ERROR] RKH's doc directory not found"
            exit 1
        fi
        echo "Done"
        cd doc/
        echo
        echo "Generating doc (html) using doxygen"
        echo "-----------------------------------"
        doxygen Doxyfile
        if [ $? = 1 ]; then
            echo "[ERROR]: doxygen raised an error"
            exit 1
        fi
        cd ..
        cp -r doc/html $argOutDir
        echo
        echo "Exporting Git repository"
        echo "------------------------"
        check_version
        echo "Exporting repository..."
        git archive --worktree-attributes -o $argOutDir/tmp_rkh_rel.zip master
        echo "Extracting repository's package..."
        unzip -qo $argOutDir/tmp_rkh_rel.zip -d $argOutDir/tmp_rkh_rel/
        echo "Copying doc (html) into package..."
        cp -rf $argOutDir/html $argOutDir/tmp_rkh_rel/doc
        echo -n "Preparing "$outdir_prefix$2"."$format" and " 
        echo $outdir_prefix$2".tar.gz files to release..."
        if [ -d $argOutDir/$outdir_prefix"$2" ]; then
            rm -rf $argOutDir/$outdir_prefix$2
        fi
        mv $argOutDir/tmp_rkh_rel $argOutDir/$outdir_prefix"$2"
        rm $argOutDir/tmp_rkh_rel.zip
        rm -rf $argOutDir/html
        cd $argOutDir/$outdir_prefix"$2"
        zip -qr ../$outfile .
        tar czf ../$outdir_prefix"$2".tar.gz .
        echo "Done"
        exit 0
        ;;
	clean)
        echo
        echo "Cleaning output directory"
        echo "-------------------------"
        [ -z $2 -o ! -d $2 ] && echo "[ERROR] Please, supply a valid deploy output directory" && exit 1
        [ $res = 1 ] && exit 1
        echo "Removing output files..."
        rm -rf $2/tmp_*/ $2/$outdir_prefix*
        rm -f $2/*.zip -r $2/html
        echo "Done"
        ;;
  	*)
        usage
        ;;
esac
exit 0

