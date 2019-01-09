# !/bin/bash -e
#
# Usage: 
#     <rkh-root>/tools/deploy$ ./rkh-deploy.sh deploy 1.0 ../../../rkh-git/ ~/out/
#

version=$1
outdir_path=$2
outdir_prefix="rkh_v"
format="zip"
outfile=$outdir_prefix"$2""."$format
outdir_name=$outdir_path"/"$outfile
res=0

usage() {
    echo "    "$0" deploy <release-version> <working-dir-path> <output-dir-path>"
    echo "    "$0" clean <output-dir-path>"
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
                echo "[WARNING] Must be realeased only from master branch"
                res=0
            fi
        fi
    else
        echo "[ERROR] <working-dir-path> ($1) is not a RKH repository"
        res=1
    fi
}

case "$1" in
	deploy)
        echo
        echo "Verifying directories and files"
        echo "-------------------------------"
        [ -z $2 ] && echo "[ERROR] Please, supplies a valid release version number" && exit 1
        [ -z $3 -o ! -d $3 ] && echo "[ERROR] Please, supplies a valid working directory" && exit 1
        [ -z $4 -o ! -d $4 ] && echo "[ERROR] Please, supplies a valid deploy output directory" && exit 1
        check_repo $3
        [ $res = 1 ] && exit 1
        echo "Testing all modules..."
        echo "Done"
        if [ ! -d doc ]; then
            echo "[ERROR] RKH's doc directory not found"
            exit 1
        fi
        cd doc/
        echo
        echo "Generating doc (html) using doxygen"
        echo "-----------------------------------"
        doc="html"
        doxygen Doxyfile
        cd ..
        cp -r doc/html $4/html/
        echo
        echo "Exporting Git repository"
        echo "------------------------"
        echo "Exporting repository into "tmp_rkh_rel.zip"..."
        git archive --worktree-attributes -o $4/tmp_rkh_rel.zip master
        echo "Extracting into "tmp_rkh_rel/"..."
        unzip -qo $4/tmp_rkh_rel.zip -d $4/tmp_rkh_rel/
        echo "Copying doc (html) into "tmp_rkh_rel/"..."
        cp -rf $4/html $4/tmp_rkh_rel/doc
        echo "Preparing ""$outdir_prefix"$2""."$format and "$outdir_prefix"$2"."tar.gz files to release for..."
        [ ! -d $4/$outdir_prefix"$2" ] && mv $4/tmp_rkh_rel $4/$outdir_prefix"$2"
        cd $4/$outdir_prefix"$2"
        zip -qr ../$outfile .
        tar czf ../$outdir_prefix"$2".tar.gz .
        echo "Done"
        exit 0
        ;;
	clean)
        echo
        echo "Cleaning output directory"
        echo "-------------------------"
        [ -z $2 -o ! -d $2 ] && echo "[ERROR] Please, supplies a valid deploy output directory" && exit 1
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

