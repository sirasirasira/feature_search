if [ $# -ne 2 ]
then
	echo "please input maxsize iteration_num"
	exit
fi

x=$1
i=$2

./bin/gtb_bandit_dag_np -x ${x} -t 1 -d 1 -i ${i} -p -1 ../../data/nci/nci_train ../../data/nci/nci_test
