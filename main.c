#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(void) {
    
	// Process & Session ID
	pid_t pid, sid;
	
	// Fork off parent
	pid = fork();
	if (pid < 0) { exit(EXIT_FAILURE); }
	
	// If PID is good, exit parent
	if (pid > 0) { exit(EXIT_SUCCESS); }
	
	// Change file mode mask
	umask(0);
	
	// Open local log
	
	// Create a new child SID
	sid = setsid();
	if (sid < 0) {
		// Log failure
		exit(EXIT_FAILURE);
	}
	
	// Change working directory
	if ((chdir("/")) < 0) {
		// Log failure
		exit(EXIT_FAILURE);
	}
	
	// Close standard file descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	// Daemon-specific initialization
	if (access("daemon.lock", F_OK) == -1) {
		int i, e;
		char ch[2];
		FILE * lock;
		FILE * log;
		lock = fopen("daemon.lock","w");
		if (lock!=NULL) {
			fputs("This will keep the daemon on a single instance.\n",lock);
			fclose(lock);
			while (1) {
				i++;
				if (i > 20) { break; }
				sprintf(ch,"%d",i);
				log = fopen("daemon.log","a");
				if (log!=NULL) {
					fputs("Iteration: ",log);
					fputs(ch,log);
					fputs("\n",log);
					fclose(log);
				}
				sleep(10);
			}
			e = remove("daemon.lock");
			if ( e > 0 ) {
				log = fopen("daemon.log","a");
				fputs("Error: Unable to delete log file\n",log);
				fclose(log);
			}
		}
	}
	exit(EXIT_SUCCESS);
}
