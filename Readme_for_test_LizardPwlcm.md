This project is mainly used to test the randonmess of LizardPwlcm with TestU01 under testingRNG project, which is released by Daniel Lemire(2018), URL https://github.com/lemire/testingRNG. 


In the directory of testu01, the program could be simply compiled as:
	make

The Test could be run simply as follows:
1) For SmallCrush:
	./testu01/testLizardPwlcm 
2) For Crush
	./testu01/testLizardPwlcm -c
3) For BigCrush
	./testu01/testLizardPwlcm -b

If the nohup and unbuffer are installed on your PC, you could run the test as:
	nohup unbuffer ./testu01/testLizardPwlcm -b 2>&1 | tee testLizardPwlcm-BigCrush.log


