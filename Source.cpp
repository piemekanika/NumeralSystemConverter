#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

int char_to_int(char c);
char int_to_char(int c);
double get_part(double x);

int main()
{
	FILE *f;
	char inp[255], out[255], buf_char;
	int b1, b2, i, length, doti, p, buf_int;
	double val, buf_dou;

	f = fopen("input.txt", "r");
	memset(out, 0, 255);
	fgets(inp, 255, f);
	fscanf(f, "%d", &b1);
	fscanf(f, "%d", &b2);
	fclose(f);

	doti = 0;
	length = strlen(inp) - 1;

	for (i = 0; i < length; i++)
	{
		if (inp[i] == '.')
		{
			doti = i;
			break;
		}
	}

	val = 0;

	for (i = (!doti) ? length - 1 : doti - 1, p = 0; i >= 0; i--, p++)
	{
		val += (char_to_int(inp[i])) * pow(b1, (double)p);
		//printf("c: %d\n%val: %lf\n", char_to_int(inp[i]), val);
	}

	if (doti)
	{
		for (i = doti + 1, p = 1; i < length; i++, p++)
		{
			val += (char_to_int(inp[i])) / pow(b1, (double)p);
		}
	}

	buf_int = (int)val;

	memset(out, 0, 255);

	for (i = 0; buf_int > 0; i++)
	{
		out[i] = int_to_char(buf_int % b2);
		buf_int /= b2;
	}

	length = strlen(out);

	for (i = 0; i < length / 2; i++)
	{
		buf_char = out[i];
		out[i] = out[length - i - 1];
		out[length - i - 1] = buf_char;
	}


	if (doti)
	{
		buf_dou = get_part(val);
		out[length] = '.';
		for (i = length + 1; buf_dou > 0 && i < length + 5; i++)
		{
			buf_dou *= b2;
			out[i] = int_to_char((int)buf_dou);
			buf_dou = get_part(buf_dou);
		}
	}

	f = fopen("output.txt", "w");
	//fputs(inp, f);
	//fprintf(f, "B1: %d\nB2: %d\nval: %lf\n", b1, b2, val);
	fputs(out, f);
	fclose(f);

	return 0;
}

int char_to_int(char c)
{
	return (c <= '9') ? c - '0' : c - 'A' + 10;
}

char int_to_char(int c)
{
	return (c <= 9) ? '0' + c : 'A' + c - 10;
}

double get_part(double x)
{
	int whol = x;
	return x - whol;
}