if [ $# -ne 1 ]
then
	echo "please input maxsize"
	exit
fi

x=$1

./gtb_bfs_stop -x ${x} -t 1 -d 1 ../../../data/nci/nci_train ../../../data/nci/nci_test

