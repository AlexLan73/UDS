specs = [ 
    legacy_code('initialize'); legacy_code('initialize'); legacy_code('initialize');
];

specs(1).OutputFcnSpec = 'write_1byte_to_uds_buffer_from_matlab(single u1)';
specs(1).SFunctionName = 'write_1byte_to_uds_buffer_from_matlab';
specs(1).HeaderFiles = { 'write_to_uds_buffer_from_matlab.h' };

specs(1).OutputFcnSpec = 'write_2byte_to_uds_buffer_from_matlab(single u1)';
specs(1).SFunctionName = 'write_1byte_to_uds_buffer_from_matlab';
specs(1).HeaderFiles = { 'write_to_uds_buffer_from_matlab.h' };

specs(1).OutputFcnSpec = 'write_3byte_to_uds_buffer_from_matlab(single u1)';
specs(1).SFunctionName = 'write_1byte_to_uds_buffer_from_matlab';
specs(1).HeaderFiles = { 'write_to_uds_buffer_from_matlab.h' };

% sfcn_cmex_generate+compile - generate .c and compiles into .mexw64; they needs for running simulink on host
legacy_code('sfcn_cmex_generate', specs);     %Generate S-function code   
legacy_code('compile', specs)                 %Compile S-function
files = dir( [ fileparts( mfilename( 'fullpath' ) ), filesep, '*.c' ] );
files = files( ~strncmpi( { files.name }, 'create_', 7 ) );
for i=1:length(files)
    disp( [ 'delete ', files(i).name ] );
    delete( files(i).name );
end

% sfcn_tlc_generate - generate .tlc files; they needs to generate sources by ert target
legacy_code('sfcn_tlc_generate', specs)       %Inline S-function by creating TLC file
% slblock_generate - generate model with S-function templates
legacy_code('slblock_generate',specs)         %Create block for S-function
legacy_code('rtwmakecfg_generate', specs)     %Add path info to RTW make file