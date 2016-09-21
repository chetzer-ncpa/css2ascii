#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cerrno>
#include <libgen.h>
#include "css.h"
#include "anyoption.h"
#include "util.h"
#include "binaryreader.h"

using namespace std;
using util::deblank;

bool wf_pointer_cmp( NCPA::CSS::Wfdisc *a, NCPA::CSS::Wfdisc *b) {
	return (*a < *b);
}
bool string_cmp( string a, string b ) { return a.compare( b ) < 0; }

bool verbose = false;

void close_waveform(vector<double> &fullwave, NCPA::CSS::Wfdisc *wf, double thistime) {

	if (fullwave.empty()) {
		return;
	}

	time_t thistime_int = (time_t)floor(thistime);
	//double thistime_dec = thistime - (double)thistime_int;
	tm *d = gmtime( &thistime_int );
	char timestr[ 16 ];
	sprintf(timestr,"%4d%02d%02d.%02d%02d%02d",d->tm_year+1900,d->tm_mon+1,
			d->tm_mday,d->tm_hour,d->tm_min,d->tm_sec);
	string filename = wf->getField("sta")->asString();
	filename += ".";
	filename += wf->getField("chan")->asString();
	filename += ".";
	filename += timestr;
	filename += ".dat";
	
	if (verbose) {
		cout << "Writing to " << filename << endl;
	}

	double calib = wf->getField("calib")->asFloat();

	ofstream outstream( filename.c_str() );
	double timeind = 0.0;
	char formatted[ 100 ];
	for (vector<double>::iterator i = fullwave.begin(); i != fullwave.end(); i++) {
		sprintf(formatted,"%.5f  %.5f",timeind,(*i) * calib);
		timeind += 1.0 / wf->getField("samprate")->asFloat();
		outstream << formatted << endl;
	}
	outstream.close();
}

int main( int argc, char **argv ) {

	// Parse input options.  We'll write this later, as it's fairly self-explanatory
	AnyOption *opt = new AnyOption();
	opt->addUsage( "Usage: ");
	opt->addUsage( "     css2ascii [options] basename" );
	opt->addUsage( "where basename is the root of the CSS database (i.e. you have basename.wfdisc," );
	opt->addUsage( " basename.site, etc)." );
	opt->addUsage( "" );
	opt->addUsage( "Options:" );
	opt->addUsage( " -h  --help              Prints this help message." );
	opt->addUsage( " -c  --channels          Specified which channels to output." );
	opt->addUsage( " -v  --verbose           Verbose mode." );
	opt->addUsage( " -d  --duration          Max segment duration [86400]." );

	opt->setCommandFlag("verbose",'v');
	opt->setCommandFlag("help",'h');
	opt->setCommandOption("channels",'c');
	opt->setCommandOption("duration",'d');

	opt->processCommandArgs( argc, argv );

	if (!opt->hasOptions()) {
		opt->printUsage();
		delete opt;
		return 1;
	}

	
	string channel_list = "";
	double maxduration = 86400.0;
	if (opt->getFlag("help") || opt->getFlag('h') ) {
		opt->printUsage();
		return 0;
	}
	if (opt->getFlag("verbose") || opt->getFlag('v')) {
		verbose = true;
	}
	if (opt->getValue( "channels" ) != NULL) {
		channel_list = opt->getValue( "channels" );
	}
	if (opt->getValue( "duration" ) != NULL) {
		maxduration = atof( opt->getValue( "duration" ) );
	}
	if (opt->getArgc() == 0) {
		cerr << "No basename specified!" << endl;
		return 1;
	}
	string basename = opt->getArgv( 0 );

	vector< string > channels;

	if (channel_list.size() > 0) {
		char *token;
		char channel_list_c[256];
		strcpy(channel_list_c,channel_list.c_str());
		token = strtok(channel_list_c,",");
		while (token != NULL) {
			string s = token;
			channels.push_back( s );
			token = strtok( NULL, "," );
		}
	}

	string wfname = basename + ".wfdisc";
	char full_wfname[ 256 ];
	if (realpath( wfname.c_str(), full_wfname ) == NULL) {
		cerr << "Can't detect full path to " << wfname << ": "
			<< strerror( errno ) << endl;
		return 1;
	}
	
	char wfname_copy[ 256 ], *wfpath_ptr;
	if (strcpy( wfname_copy, full_wfname ) == NULL) {
		cerr << "Can't copy pathname: " << strerror( errno ) << endl;
		return 1;
	}
	wfpath_ptr = dirname( wfname_copy );
	string wfpath = wfpath_ptr;
	if (verbose) {
		cout << "Full .wfdisc file is " << full_wfname << endl
			<< "Base path is " << wfpath << endl;
		
	}

	vector< NCPA::CSS::Wfdisc * > wfdiscs;
	vector< NCPA::CSS::Wfdisc * >::iterator wf_iterator;
	ifstream wfstream( full_wfname );
	string wfline;
	std::getline( wfstream, wfline );
	while (wfline.length() == 283) {
		NCPA::CSS::Wfdisc *wfdisc = new NCPA::CSS::Wfdisc( wfline );
		vector< string >::iterator it;
		it = find( channels.begin(), channels.end(), wfdisc->getField("chan")->asString() );
		if (channels.empty() || it != channels.end())
			wfdiscs.push_back( wfdisc );
		std::getline( wfstream, wfline );
	}

	sort( wfdiscs.begin(), wfdiscs.end(), wf_pointer_cmp );

	// Iterate through the vector.  We want to get a unique list of station/channel pairs,
	// plus find the overall start time of the file
	double file_start_time = 99999999999.9;
	set< string > stachans;
	map< string, int > stachan_indices;
	int index = 0;
	for (wf_iterator = wfdiscs.begin(); wf_iterator != wfdiscs.end(); wf_iterator++) {
		NCPA::CSS::Wfdisc *thiswf = *wf_iterator;
		string stachan = thiswf->getField("sta")->asString();
		stachan += ":";
		stachan += thiswf->getField("chan")->asString();
		stachans.insert( stachan );
		stachan_indices[ stachan ] = index++;
		double wftime = thiswf->getField("time")->asFloat();
		file_start_time = wftime < file_start_time ? wftime : file_start_time;
	}

	// Now we have to define some time variables, cause there will be several 
	// floating around.
	// wfdisc_start_time: the time the current waveform "should" start
	// segment_start_time: the starting time of the current .wfdisc segment
	double wfdisc_start_time = file_start_time;
	double segment_start_time;
	vector< double > fullwave;
	map< string, double > starttimes;
	index = 0;
	BinaryReader *binread = new BinaryReader();

	for (set< string >::iterator i = stachans.begin(); i != stachans.end(); i++) {
		string thispair = *i;
		size_t separator = thispair.find_first_of(":");
		string sta = thispair.substr(0,separator);
		string chan = thispair.substr(separator+1);

		starttimes[ sta ] = file_start_time;
		if (verbose) { cout << thispair << endl; }
		fullwave.clear();
		segment_start_time = file_start_time;
		for ( ; index <= stachan_indices[ thispair ]; index++) {
			double samprate = wfdiscs[ index ]->getField("samprate")->asFloat();
			double sampper = 1.0/samprate;
			unsigned int maxsamples = (unsigned int)floor(maxduration * samprate);
			fullwave.reserve( maxsamples );
			
			// Figure out if there is any time missing that needs to be filled in
			double timegap = wfdiscs[ index ]->getField("time")->asFloat() 
					- wfdisc_start_time;
			int samples_missing = (int)floor( timegap * samprate );
			if (fabs(timegap * samprate - samples_missing) >= 0.5)
				samples_missing++;
			while(samples_missing-- > 0) {
				fullwave.push_back(0.0);
				if (fullwave.size() == maxsamples) {
					close_waveform(fullwave,wfdiscs[index],segment_start_time);
					segment_start_time += maxduration;
					fullwave.clear();
				}
			}

			// read in the waveform data
			string wfilename = wfpath + "/" + wfdiscs[ index ]->getField("dir")->asString();
			if (wfilename[ wfilename.length()-1 ] != '/') {
				wfilename += "/";
			}
			wfilename += wfdiscs[ index ]->getField("dfile")->asString();
			cout << "Reading " << wfilename << endl;
			ifstream wstream( wfilename.c_str(), ios_base::in | ios_base::binary );
			if (wstream.fail()) {
				cerr << "Error opening file " << wfilename << endl;
				return 1;
			}
			wstream.seekg( wfdiscs[ index ]->getField("foff")->asInt() );
			int nsamp = wfdiscs[ index ]->getField("nsamp")->asInt();
			double *temparray = new double[ nsamp ];
			binread->readFromCSSCode( &wstream, nsamp, 
					wfdiscs[ index ]->getField("datatype")->asString(),
					temparray );
			for (int k = 0; k < nsamp; k++) {
				fullwave.push_back( temparray[ k ] );
				if ( fullwave.size() == maxsamples) {
					close_waveform(fullwave,wfdiscs[index],segment_start_time);
					segment_start_time += maxduration;
					fullwave.clear();
				}
			}
			wfdisc_start_time = wfdiscs[ index ]->getField("endtime")->asFloat() 
					+ sampper;
			delete [] temparray;
		}

		close_waveform(fullwave,wfdiscs[index-1],segment_start_time);
		wfdisc_start_time = file_start_time;
	}


	// calculate relative coordinates from site file.  to be implemented later as needed.

}

