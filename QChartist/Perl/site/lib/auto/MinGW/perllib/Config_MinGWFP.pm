#########################################################################################
# Package       Config_MinGWFP
# Description:  Configure MinGW
# Created       Sat Jul 16 12:41:28 2011
# SVN Id        $Id:$
# Copyright:    Copyright (c) 2011 Mark Dootson
# Licence:      This program is free software; you can redistribute it 
#               and/or modify it under the same terms as Perl itself
#########################################################################################
#
# This module overrides Config returning correct values for GCC with Perl compiled with
# MS tools. ( e.g. ActivePerl ).
# It will also create lib\CORE\libperl5xx.a so your Perl tree needs to be writeable.
# Should work with any MinGW
#
# For easiest usage, set the environment variable:
#
# set PERL5OPT=-MConfig_MinGWFP
#
#########################################################################################

BEGIN { $ENV{ACTIVEPERL_CONFIG_DISABLE} = 1; }

package Config_MinGWFP;
use strict;
use warnings;
use Cwd;
use Config;
use File::Copy;
use Storable;

our $VERSION = '0.20';

our $_checkversion = 20;

our $gccconfig = { CHECKVERSION => $_checkversion, currentlibperlversion => '0' };

if( _new_config_required() ) {
    _set_gcc_version();
    _set_gcc_paths();
    _set_gcc_cflags();
    _set_gcc_libs();
    _set_gcc_lflags();
    eval {
        Storable::lock_nstore( $gccconfig, $gccconfig->{thisconfigfile} );
    };
    die qq(Config_MinGWFP failed to save $gccconfig->{thisconfigfile} : $@) if $@;
}

_test_make_libperl();

my %values = (
    cc          => 'gcc',
    ccname      => 'gcc',
    ccflags     => $gccconfig->{ccflags},
    _a          => '.a',
    _o          => '.o',
    ar          => 'ar',
    cpp         => 'gcc -E',
    libpth      => $gccconfig->{libpth},
    cppminus    => '-',
    cpprun      => 'gcc -E',
    cppstdin    => 'gcc -E',
    ccversion   => '',
    gccversion  => $gccconfig->{gccversion},
    incpath     => $gccconfig->{incpath},
    ld          => 'g++',
    lddlflags   => $gccconfig->{lddlflags},
    ldflags     => $gccconfig->{ldflags},
    lib_ext     => '.a',
    libc        => '',
    libperl     => $gccconfig->{libperl},
    make        => 'dmake',
    nm          => 'nm',
    obj_ext     => '.o',
    optimize    => '-s -O2',
    libs        => $gccconfig->{libs},
    perllibs    => $gccconfig->{libs},
    i64type     => 'long long',
    u64type     => 'unsigned long long',
    quadtype    => 'long long',
    uquadtype   => 'unsigned long long',
    d_casti32   => 'define',
);
    
{
    my $obj = tied %Config::Config;
    foreach my $key(sort keys(%values)) {
        $obj->{$key} = $values{$key};
    }
}

sub _new_config_required {
    my $rval = 1;
    my $perlpath = Cwd::realpath($^X);
    my @plpaths = split(/[\\\/]+/, $perlpath);
    pop(@plpaths); # lose gcc.exe
    pop(@plpaths); # lose bin
    $gccconfig->{perlprefix} = join(qq(\\), @plpaths);
    $gccconfig->{thisconfigfile} = qq($gccconfig->{perlprefix}/lib/CORE/mingwforperlconfig.dat);
    if( -f $gccconfig->{thisconfigfile} ) {
        eval {
            $gccconfig = Storable::lock_retrieve($gccconfig->{thisconfigfile});
        };
        die qq(Config_MinGWFP failed to load $gccconfig->{thisconfigfile} : $@) if $@;
        $rval = ( $gccconfig->{CHECKVERSION} != $_checkversion );
    }
    return $rval;
}

sub _set_gcc_version {
    
    # GCC Version
    my $gccversionstring = qx(gcc -dumpversion);
    chomp( $gccversionstring );

    if( $gccversionstring =~ /^(\d+\.\d+\.\d+)$/ ) {
        $gccconfig->{gccversion} = $1;
    } else {    
        die "Unable to locate GCC";
    }
    
    my($major,$minor,$release) = split(/\./, $gccversionstring);

}

sub _set_gcc_paths {
    # Libpath and IncPath
    # we add all possible paths even if MinGW.org does not
    # have them
    
    my $gccroot = qx(gcc --print-file-name=gcc);
    $gccroot = Cwd::realpath($gccroot);
    
    my @gccpaths = split(/[\\\/]+/, $gccroot);
    pop(@gccpaths); # lose gcc
    pop(@gccpaths); # lose bin
    $gccroot = join(qq(\\), @gccpaths);
    
    if( $Config{ptrsize} == 8 ) {
        # lib and inc paths for 64 bit compilsation
        $gccconfig->{libpth}  = qq(\"$gccroot\\lib\" \"$gccroot\\lib64\" \"$gccroot\\x86_64-w64-mingw32\\lib\" \"$gccroot\\x86_64-w64-mingw32\\lib64\");
        $gccconfig->{incpath} = qq(\"$gccroot\\include\" \"$gccroot\\x86_64-w64-mingw32\\include\");
    } else {
        # lib and inc paths for 32 bit compilation
        $gccconfig->{libpth}  = qq(\"$gccroot\\lib\" \"$gccroot\\lib32\" \"$gccroot\\i686-w64-mingw32\\lib\" \"$gccroot\\x86_64-w64-mingw32\\lib32\");
        $gccconfig->{incpath} = qq(\"$gccroot\\include\" \"$gccroot\\i686-w64-mingw32\\include\" \"$gccroot\\x86_64-w64-mingw32\\include\");
    }
    
    $gccconfig->{gccroot} = $gccroot;
    
}

sub _set_gcc_cflags {
    # CCFLAGS
    $gccconfig->{ccflags} = ' -s -O2';
    
    my @configs = split(/\s+/, $Config{ccflags});
    for my $cgfdefine ( @configs ) {
        if( $cgfdefine && ($cgfdefine =~ /^-D/) ) { $gccconfig->{ccflags} .= ' ' . $cgfdefine; } 
    }
    
    $gccconfig->{ccflags} .= ' -DHASATTRIBUTE -fno-strict-aliasing -mms-bitfields';
    
    $gccconfig->{ccflags} .= ( $Config{ptrsize} == 8 ) ? ' -m64' : ' -m32';
        
}


sub _set_gcc_libs {
    # Libperl & PerlLibs
    # Create an import lib if none exists
    
    my $basedll = $Config{libperl};
    $basedll =~ s/lib$/dll/i;
    my $basedef = $basedll;
    $basedef =~ s/dll$/def/i;
    my $libperl = $basedll;
    $libperl =~ s/^perl/libperl/;
    $libperl =~ s/dll$/a/i;
    
    $gccconfig->{libperl} = $libperl;
    
    $gccconfig->{libs} = ' -lmoldname -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -lnetapi32 -luuid -lws2_32 -lmpr -lwinmm -lversion -lodbc32 -lodbccp32 -lcomctl32';
    
    $gccconfig->{fullperllibpath} = qq($gccconfig->{perlprefix}\\lib\\CORE\\$libperl);
    $gccconfig->{fullperldllpath} = qq($gccconfig->{perlprefix}\\bin\\$basedll);
    $gccconfig->{fullperldefpath} = qq($gccconfig->{perlprefix}\\lib\\CORE\\$basedef);
    
    my $gendefexe = qq($gccconfig->{gccroot}\\bin\\gendef.exe);
    $gccconfig->{hasgendef} = ( -f $gendefexe ) ? 1 : 0;
        
}

sub _set_gcc_lflags {

    # Linker Flags
    my $compflag = ( $Config{ptrsize} == 8 ) ? '-m64' : '-m32';
    $gccconfig->{ldflags} = qq(-s $compflag -L\"$gccconfig->{perlprefix}\\lib\\CORE\");
    $gccconfig->{lddlflags} = qq(-s -mdll $compflag -L\"$gccconfig->{perlprefix}\\lib\\CORE\");

}
    

sub get_configured_values {
    my @keys = sort keys(%values);
    my %output = ();
    for my $key ( @keys ) {
        $output{$key} = $Config{$key};
    }
    return \%output;
}


sub print_configured_values {
    my $configs = get_configured_values();
    print qq(Config_MinGW Configured Values ..\n);
    foreach my $key ( sort keys(%$configs) ) {
        print qq(    $key = $configs->{$key}\n);
    }
}

sub _test_make_libperl {
    my $checkperlversion = qq($]);
    my $newlibrequired = !$gccconfig->{currentlibperlversion};
    $newlibrequired ||=  ! -f $gccconfig->{fullperllibpath};
    $newlibrequired ||= ( $checkperlversion ne $gccconfig->{currentlibperlversion} );
    if( $newlibrequired ) {
        make_libperl();
        $gccconfig->{currentlibperlversion} = $checkperlversion;
        eval {
            Storable::lock_nstore( $gccconfig, $gccconfig->{thisconfigfile} );
        };
        die qq(Config_MinGWFP failed to save $gccconfig->{thisconfigfile} : $@) if $@;
        if( !-f $gccconfig->{fullperllibpath} ) {
            die q(Failed to find libperl import library and could not create it);
        }
    }
}

sub make_libperl {
    unlink($gccconfig->{fullperldefpath});
    unlink($gccconfig->{fullperllibpath});
    # do we have gendef ?
    if( $gccconfig->{hasgendef} ) {
        my $defdata = qx(gendef - $gccconfig->{fullperldllpath});
        open my $fh, '>', $gccconfig->{fullperldefpath};
        print $fh $defdata;
        close($fh);
    } else {
        die 'Install gendef to produce libperl5xx.a';
    }
    
    my $command = qq(dlltool --kill-at --input-def $gccconfig->{fullperldefpath} --output-lib $gccconfig->{fullperllibpath});
    system($command) && die qq($command failed $!);
    
}

1;

__END__





