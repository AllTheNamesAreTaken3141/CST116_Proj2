#include <iostream>
#include <windows.h> // Allows access to windows system commands and other associated black magic.
#include <string> // Required for the getline in the whitespaceInput function below, but useful in a lot of other cases too.

using namespace std;

#pragma region colorprints // This isn't C++, it's a VS thing that lets you collapse the entire section. Very useful for keeping your code organized.

const HANDLE HCONSOLE = GetStdHandle(STD_OUTPUT_HANDLE); // I'm like 90% sure that this is an address that points to the console and lets us mess with it.

// Uses those system commands I mentioned to print in full color (color_codes.txt has the codes for all 16 colors) with (optional) automatic line breaks. If you end up needing/wanting to put multiple colors on the line then send me a message. I have a function that'll do it without you having to stack this one a bunch of times, but it's a pain to use so I'm not going to add it unless I need to. Anyway, this one takes up to 4 parameters, but you'll probably only ever end up using the first two.
// text (string): The text to be printed. Don't put a newline at the end.
// color (int): The color code of the text. Optional, defaults to white.
// linebreak (bool): Whether to end the line after printing. Optional, defaults to true.
// console (HANDLE) the console the function is printing to, used for changing color. Defaults to HCONSOLE so you can just ignore it.
void colorPrint(string text, int color = 15, bool linebreak = true, HANDLE console = HCONSOLE)
{
	SetConsoleTextAttribute(console, color); // Change the output color to whatever is chosen for the text (defaults to 15, which is white).
	cout << text;
	SetConsoleTextAttribute(console, 15); // Set the color back to white so that we don't start randomly printing other colors.
	if (linebreak) // Add a line break to the end of the text if needed.
	{
		cout << endl;
	}

}


// It turns out that cin will usually break when you input a string that has whitespace in it, so I wrote this to fix it. Feel free to stick with cin if you're not trying to get input with whitespace, though.
string whitespaceInput()
{
	string input;
	string afterWhitespace;
	cin >> input; // cin stops reading input when it reaches any whitespace, but it doesn't get rid of what's left. Not only does that mean you lose anything the user typed after that whitespace, but it also breaks cin the next time you call it. cin (as far as I can tell) doesn't actually wait for user input, it just waits until there's something in the "input buffer". Since there's still input in the buffer, the next cin you call will see that there's something in the buffer and immediately read it instead of letting the user input something new.

	getline(cin, afterWhitespace); // getline gets input from the buffer like cin does, except that it ignores whitespace, and it doesn't wait for something to be in the buffer (if there's nothing there when you call it, it just returns an empty string). I'm using it here as a sort of "cleanup" function to grab anything that's left in the buffer after the cin.

	input += afterWhitespace; // Combine the input from the cin with anything that getline picked up.

	return input;
}

#pragma endregion

int main()
{
	colorPrint("Hello World!", 9);

	return 0;
}