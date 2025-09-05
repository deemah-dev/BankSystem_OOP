#include"clsInputValidate.h";
#include"clsLoginScreen.h";

int main() {
	while (1) {
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}
}
