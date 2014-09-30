dnl Function to detect if libolecf dependencies are available
AC_DEFUN([AX_LIBOLECF_CHECK_LOCAL],
 [dnl Check for internationalization functions in libolecf/libolecf_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

