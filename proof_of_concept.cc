//
// stripped off project no_efi
// implement the lines in your project
//

const u64 variable_control_data( u64 variable_prefix, u64 arg2, u64 arg3 )
{
    switch( variable_prefix )
    {
	case e_operations::read:
	     mem::rw_phys( false, functify( arg2 ).to( comm_struct ) );
	     break;
	case e_operations::write:
	     mem::rw_phys( true, functify( arg2 ).to( comm_struct ) );
	     break;
	case e_operations::image:
	     mem::image( functify( arg2 ).to( comm_struct ) );
	     break; 
    }
}

NTSTATUS p_driver_entry( u64 image, u64 mapped, u64 vuln_drv_image, u64 uncleared )
{
  	const auto uefi_total_variable_count = IDA( "40 53 4C 83 EC 20 4C 8B DA 48 8C 64 24 ? ?" ).find( windows_boot_mgfw );
	if ( uefi_total_variable_count )
	{
	    // VARIABLE_NAME -> pchtaorl
	    KLI_FN( memcpy )( reinterpret_cast<u64*>( *this->ctx->get_variables( ) ), VARIABLE_NAME, sizeof const char* ) );
            *this->ctx->get_variables( )->device[0xcc] = variable_control_data;
	} 
} 


//
// example usage in your usermode program
// must be executed in a thread running in a loop
//
if( &module_information )
{
    const auto loaded_objects = ke_service_descriptor_table[0xAC];
    // LoadedObjectDescriptor->OutputData = 0x72
    loaded_objects.get_command( VARIABLE_NAME, comm_struct, sizeof comm_struct ); 
}
