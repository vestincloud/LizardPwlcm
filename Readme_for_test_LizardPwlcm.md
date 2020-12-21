This project is mainly used to test the randonmess of LizardPwlcm under TestU01.

In the directory of testu01, the program could be simply compiled as:
	make

The Test could be run simply as follows:
1) For SmallCrush:
	./testu01/testLizardPwlcm 
2) For Crush
	./testu01/testLizardPwlcm -c
3)For BigCrush
	./testu01/testLizardPwlcm -b

If the nohup and unbuffer are installed in your PC, you could run the test as:
	nohup unbuffer ./testu01/testLizardPwlcm -b 2>&1 | tee testLizardPwlcm-Crush.log


