if [ $# -ne 1 ]
then
	echo "please input maxsize "
	exit
fi

x=$1

./bin/gtb_bandit_tree_sim -x ${x} -t 1 -d 1 -p -1 -c 1 ./data/nci/nci_train ./data/nci/nci_test
