/*
	FinalAssignment.cpp
		code by Jack Magnusson 4/29/18
		Final Assignment csci-e53
*/

#include <iostream>
#include "Location.h"
#include "Product.h"
#include "process.h"


using namespace std;

time_t currentTime = 2592000;

int main()
{	
	// make Database
	Database db;

	cout << "*****************MAKING ACCOUNT WITH ONE NEW MEMBER********************" << endl;
	unsigned blobAcctId = getNewId(), clobId = getNewId();
	processNewAccount(db,
		Member(clobId, blobAcctId, "Clob Blobson", "Blob and Blobson", enum2Prod(FullTime), BOS));
	db.display();

	cout << "*****************ADDING ANOTHER MEMBER TO SAME ACCOUNT******************" << endl;
	
	unsigned blobId = getNewId();
	processNewMember(db,
		Member(blobId, blobAcctId,"Blob Nobdottir", "Blob and Blobson", enum2Prod(PartTime), NYC));
	db.display();

	cout << "*****************CHANGE ACCOUNT OWNER TO NEW MEMBER******************" << endl;
	processAccountOwnerChange(db, blobId);
	db.display();

	cout << "*****************USE EXACTLY ALL USAGE ALLOCATIONS******************" << endl;

	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);
	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);
	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);
	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);
	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);

	processMeetingRoomUsage(db, clobId, 10);
	processMeetingRoomUsage(db, blobId, 15);

	db.display();

	cout << "**********EACH MEMBER USES ONE MORE DAY, AND A TOTAL OF 3 MORE MEETING ROOM HOURS*******" << endl;

	processDayUsage(db, clobId);
	processDayUsage(db,	blobId);

	processMeetingRoomUsage(db, clobId, 1);
	processMeetingRoomUsage(db, blobId, 2);

	db.display();

	cout << "*****************ADD MAILING AND STORAGE SERVICES******************" << endl;
	processAddService(db, blobAcctId, enum2String(Mailing));
	processAddService(db, blobAcctId, enum2String(Storage));
	db.display();

	cout << "*****************CHANGE CLOB'S MEMBERSHIP TO INACTIVE, REMOVE MAILING******************" << endl;
	
	processMembershipChange(db, clobId, enum2String(Inactive));
	processRemoveService(db, blobAcctId, enum2String(Mailing));
	db.display();

	cout << "*********ONE MONTH PASSES, USAGE ALLOCATIONS ARE RESET, AND RECURING FEES TAKEN*********" << endl;

	processUsageAllocationReset(db);
	currentTime += 2592000;
	processRecurringFees(db);
	db.display();

	cout << "*****************CHANGE BLOB'S MEMBERSHIP TO OFFICE******************" << endl;
	
	processMembershipChange(db, blobId, enum2String(Office));
	db.display();

	cout << "**************GO ONE PAST MEETING ROOM ALLOCATIONS, ALSO TRY LOTS OF DAYS************" << endl;

	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);
	processDayUsage(db,	blobId);

	processMeetingRoomUsage(db, blobId, 21);

	db.display();

	cout << "**************CHARGE GUEST PASS AND PRINTING TO ACCT************" << endl;
	processOneTimeProduct(db, blobId, enum2String(GuestPass));
	processOneTimeProduct(db, blobId, enum2String(BWPrint), 100);

	db.display();

	cout << "**************LOOK UP BLOB BY NAME AND DISP, LOOK UP ACCT BY OWNER AND DISP************" << endl;

	db.lookUpMemberByName("Blob Nobdottir").display();
	db.lookUpAccountByOwner(blobId).display();

	return 0;
}

