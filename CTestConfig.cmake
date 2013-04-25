# Set the project name
SET(CTEST_PROJECT_NAME "Xip")

# Dashboard is opened for submissions for a 24 hour period starting at
# the specified NIGHLY_START_TIME. Time is specified in 24 hour format.
SET (CTEST_NIGHTLY_START_TIME "23:00:00 EDT")

SET(CTEST_DROP_METHOD xmlrpc) 
SET(CTEST_DROP_SITE "http://pccs945c.us008.siemens.net:8081")
SET(CTEST_DROP_LOCATION "Xip")
SET(CTEST_COMPRESS_SUBMISSION ON)

# Dashboard is opened for submissions for a 24 hour period starting at
# the specified NIGHLY_START_TIME. Time is specified in 24 hour format.
SET (NIGHTLY_START_TIME "23:00:00 EDT")

# Dart server to submit results (used by client)
IF(NOT DROP_METHOD)
  SET(DROP_METHOD xmlrpc)
ENDIF(NOT DROP_METHOD)
IF(DROP_METHOD MATCHES xmlrpc)
  SET (DROP_SITE "http://pccs945c.us008.siemens.net:8081")
#  SET (DROP_LOCATION "/cgi-bin/HTTPUploadDartFile.cgi")
ELSE(DROP_METHOD MATCHES xmlrpc)
  SET (DROP_SITE "http://pccs945c.us008.siemens.net:8081")
  SET (DROP_LOCATION "/incoming")
  SET (DROP_SITE_USER "ftpuser")
  SET (DROP_SITE_PASSWORD "public")
ENDIF(DROP_METHOD MATCHES xmlrpc)

#SET (TRIGGER_SITE 
#       "http://${DROP_SITE}/cgi-bin/Submit-vtk-TestingResults.pl")

# Project Home Page
#SET (PROJECT_URL "http://www.vtk.org")

# Dart server configuration 
#SET (ROLLUP_URL "http://${DROP_SITE}/cgi-bin/vtk-rollup-dashboard.sh")
#SET (CVS_WEB_URL "http://${DROP_SITE}/cgi-bin/viewcvs.cgi/")
#SET (CVS_WEB_CVSROOT "VTK")
#SET (USE_DOXYGEN "On")
#SET (DOXYGEN_URL "http://www.vtk.org/doc/nightly/html/" )
#SET (GNATS_WEB_URL "${PROJECT_URL}/Bug/query.php?projects=1&status%5B%5D=1&status%5B%5D=2&status%5B%5D=3&status%5B%5D=4&status%5B%5D=6&op=doquery")
#SET (USE_GNATS "On")

# copy over the testing logo
#CONFIGURE_FILE(${VTK_SOURCE_DIR}/TestingLogo.gif ${VTK_BINARY_DIR}/Testing/HTML/TestingResults/Icons/Logo.gif COPYONLY)

# Continuous email delivery variables
SET(CONTINUOUS_FROM "sylvain.jaume@siemens.com")
SET(SMTP_MAILHOST "lte-scr.usa.siemens.com")
SET(CONTINUOUS_MONITOR_LIST "sylvain.jaume@siemens.com thomas.moeller@siemens.com patric.ljung@siemens.com")
SET(CONTINUOUS_BASE_URL "${PROJECT_URL}/Testing")

SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_FAILURES ON)
SET(DELIVER_BROKEN_BUILD_EMAIL "Continuous Nightly")
SET(EMAIL_FROM "sylvain.jaume@siemens.com")
SET(DARTBOARD_BASE_URL "${PROJECT_URL}/Testing")

SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_CONFIGURE_FAILURES 1)
SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_BUILD_ERRORS 1)
SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_BUILD_WARNINGS 1)
SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_NOT_RUNS 1)
SET(DELIVER_BROKEN_BUILD_EMAIL_WITH_TEST_FAILURES 1)


