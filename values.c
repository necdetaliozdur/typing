/*
 *  values.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/23/09.
 *
 */

#include "values.h"

int initValues()
{
	int i;

	initCosts();

	if (fullKeyboard == K_NO) {
		// Set keyboard position costs. These costs were determined by looking
		// at how the positions were valued on some of the best alternative
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  70,  80,  40,  30,  40,  40,
			  0,   0,   0,   0,  30,  30,   0,   0,   0,   0,
			 70,  70,  70,  50,  95,  60,  40,  60,  70,  70,
		};

		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_STANDARD) {

		// These costs are optimized for a full standard layout. Any cost that
		// is 999 is not supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  40,  40,  30,  40,  70,  80,  40,  30,  40,  40,  60,  90, 140,
			999,   0,   0,   0,   0,  30,  30,   0,   0,   0,   0,  50, 999, 999,
			999,  70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 999, 999, 999,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_KINESIS) {

		// These costs are optimized for Kinesis. Any cost that is 999 is not
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			120, 110, 100,  75, 100, 130, 130, 100,  75, 100, 110, 120,
			 90,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40,  90,
			 60,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  60,
			999,  70,  70,  70,  50,  80,  80,  50,  70,  70,  70, 999,
			999, 140, 140, 999, 999, 999, 999, 999, 999, 140, 140, 999,
			  0,  50, 999, 999, 999, 999, 999, 999, 999, 999,  50,   0,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_IPHONE) {

		// Thumbs are centered over the QWERTY D and K keys.
		static int64_t costsCopy[KSIZE_MAX] = {
			  45,  30,  20,  10,  20,  20,  10,  20,  30,  40,
			  20,  10,   0,   0,  10,  10,   0,   0,  10, 999,
			 999,  60,  50,  30,  20,  20,  50,  60, 999, 999,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	}

	// Based on distance from the ctrl key and how much of a stretch it is.
	return 0;
}

void initCosts()
{
	detailedOutput = TRUE;

    /* If you do not wish to use multithreading, set numThreads to 1. */
	numThreads = 1;

	keepNumbers = 1;
	keepBrackets = TRUE;
	keepShiftPairs = FALSE;
	keepTab = TRUE;
	keepConsonantsRight = FALSE;
	keepNumbersShifted = FALSE;

	bracketsCost = 5000000;
	numbersShiftedCost = -1000000;

	if (fullKeyboard == K_KINESIS) {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  7.5;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 10.0;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 20.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 20.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;
	} else {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  9.0;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 11.5;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 22.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 22.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;
	}

	fingerWorkCosts[0] = fingerWorkCosts[FINGER_COUNT - 1] = 40;
	fingerWorkCosts[1] = fingerWorkCosts[FINGER_COUNT - 2] = 30;
	fingerWorkCosts[2] = fingerWorkCosts[FINGER_COUNT - 3] = 20;
	fingerWorkCosts[3] = fingerWorkCosts[FINGER_COUNT - 4] = 20;
	fingerWorkCosts[4] = fingerWorkCosts[FINGER_COUNT - 5] = 20;

	/* All values are compounding. For example, say we jump over the home row
	 * on the index finger. The cost is
     *     sameHand + rowChange + homeJump + homeJumpIndex.
     */
	distance =		  1;
	inRoll =		-40;
	outRoll =		  5;
	sameHand =		  5;
	sameFingerP =	150;
	sameFingerR =	140;
	sameFingerM =	110;
	sameFingerI =	 90;
	sameFingerT =	100;
	rowChangeDown =  10;
	rowChangeUp =    15;
	handWarp =		 25;
	handSmooth =	- 5;
	homeJump =		100;
	homeJumpIndex = -90;
	doubleJump =	220; /* Does not compound with homeJump. */
	ringJump =       40;
	toCenter =		 30;
	toOutside =		 30;
	shiftCost =		100;
	doubleShiftCost=150;
}
