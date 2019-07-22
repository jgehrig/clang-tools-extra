// RUN: %check_clang_tidy %s microsoft-uniform-initialization %t

//
// Global Scope Variable Checks
//
int error_global_var_noinit;
// CHECK-MESSAGES: [[@LINE-1]]:5: warning: variable 'error_global_var_noinit' does not use uniform initialization [microsoft-uniform-initialization]
// CHECK-FIXES: int error_global_var_noinit {};

int error_global_var_cinit = 1 + 2 + 3;
// CHECK-MESSAGES: [[@LINE-1]]:5: warning: variable 'error_global_var_cinit' does not use uniform initialization [microsoft-uniform-initialization]
// CHECK-FIXES: int error_global_var_cinit { 1 + 2 + 3 };

int valid_global_var { 123 };
extern int valid_gobal_extern_var;


//
// Class Member Variable Checks
//
class TestClass
{
	static int error_static_member_var;
	static int valid_static_member_var;

	int error_member_var_noinit;
	// CHECK-MESSAGES: [[@LINE-1]]:6: warning: class member variable 'error_member_var_noinit' does not use uniform initialization [microsoft-uniform-initialization
	// CHECK-FIXES: int error_member_var_noinit {};

	int error_member_var_cinit = 1;
	// CHECK-MESSAGES: [[@LINE-1]]:6: warning: class member variable 'error_member_var_cinit' does not use uniform initialization [microsoft-uniform-initialization
	// CHECK-FIXES: int error_member_var_cinit { 1 };

	int valid_member_var { 0 };
};

int TestClass::error_static_member_var = 0;
// CHECK-MESSAGES: [[@LINE-1]]:16: warning: variable 'error_static_member_var' does not use uniform initialization [microsoft-uniform-initialization]

int TestClass::valid_static_member_var { 0 };


//
// Function Scoped Variable Checks
//
void TestFunction()
{
	static int error_static_local_var = 1234;
	// CHECK-MESSAGES: [[@LINE-1]]:13: warning: variable 'error_static_local_var' does not use uniform initialization [microsoft-uniform-initialization]
	// CHECK-FIXES: int error_static_local_var { 1234 };

	static int valid_static_local_var { 0 };

	int error_local_var_noinit;
	// CHECK-MESSAGES: [[@LINE-1]]:6: warning: variable 'error_local_var_noinit' does not use uniform initialization [microsoft-uniform-initialization]
	// CHECK-FIXES: int error_local_var_noinit {};

	int error_local_var_cinit = 1;
	// CHECK-MESSAGES: [[@LINE-1]]:6: warning: variable 'error_local_var_cinit' does not use uniform initialization [microsoft-uniform-initialization]
	// CHECK-FIXES: int error_local_var_cinit { 1 };

	int valid_local_var { 0 };
}
