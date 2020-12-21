Assuming Linux or macOS. Go to a bash shell and type:

	make

For testing LIZARD-PWLCM just simply  follows:
1) For Small Crush
	./testLizardPwlcm 
2) For Crush
	./testLizardPwlcm -c
3) For Big Crush
	./testLizardPwlcm -b

If the nohub and unbuffer are available on your PC, you could:
	nohub unbuffer ./testLizardPwlcm -b 2>&1 | tee testLizardPwlcm-BigCrush.log
