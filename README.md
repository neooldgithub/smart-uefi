# smart_uefi

this project takes advantage of how EFI drivers communicate (by hooking SetVariable and such)

in this short project, we get a list of the EFI variables and place our communicated buffer structure in the first loaded variable object that comes up that we then communicate with using the KeServiceDescriptorTable, all required offsets are listed.
