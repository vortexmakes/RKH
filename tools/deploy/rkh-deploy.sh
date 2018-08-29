#!/bin/bash
# Usage: 
# lf@razor:~/rkh$ .././rkh-deploy.sh 3.0.0 ../rkh-release
# lf@razor:~/rkh$ .././rkh-deploy.sh clean ../rkh-release

version=$1
outdir_path=$2
outdir_prefix="rkh_v"
format="zip"
outfile=$outdir_prefix"$2""."$format
outdir_name=$outdir_path"/"$outfile
res=0

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
                echo "[WARNING] Must be realeasing only for master branch"
                res=0
            fi
        fi
    else
        echo "[ERROR] <working-dir-path> ($1) is not a RKH repository"
        res=1
    fi
}

usage() {
    echo "      "$0" deploy <release-version> <working-dir-path> <output-dir-path> [<html-dir-path>]"
    echo "      "$0" clean <working-dir-path>"
    echo "      "$0" check <working-dir-path>"
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
        cp -r doc/html $curr_dir/$4/html/
        echo
        echo "Exporting Git repository"
        echo "------------------------"
        echo "Archiving repository into "$curr_dir/$4/tmp_rkh_rel.zip"..."
        git archive --worktree-attributes -o $curr_dir/$4/tmp_rkh_rel.zip master
        echo "Unpacketing archive file into "$curr_dir/$4/tmp_rkh_rel/"..."
        unzip -qo $curr_dir/$4/tmp_rkh_rel.zip -d $curr_dir/$4/tmp_rkh_rel/
        echo "Copying doc (html) into "$curr_dir/$4/tmp_rkh_rel/"..."
        cp -rf $curr_dir/$4/html $curr_dir/$4/tmp_rkh_rel/doc
        echo "Preparing "$curr_dir/$4"/$outdir_prefix"$2""."$format file to release for..."
        [ ! -d $curr_dir/$4/$outdir_prefix"$2" ] && mv $curr_dir/$4/tmp_rkh_rel $curr_dir/$4/$outdir_prefix"$2"
        cd $curr_dir/$4/$outdir_prefix"$2"
        zip -qr ../$outfile .
        cd $curr_dir
        exit 0

        ;;
	check)
        if [ -z $2 ]; then
            echo "[ERROR] Please, supplies a valid RKH working directory"
            usage
        else
            check_repo $2
            [ $? = 1 ] && exit 1
        fi
        ;;
	clean)
        check_repo $3
        [ $res == 1 ] && exit 1
        echo "Cleaning output directory "$outdir_path
        rm -r $outdir_path/tmp_*/ $outdir_path/$outdir_prefix*
        rm $outdir_path/*.zip
        ;;
  	*)
        usage
        ;;
esac
exit 0

