package org.northfuse.documentation;

import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class DocGenerator
{
	final static String latex_template = "\\subsection{<!--name--!>}\n\\bf{<!--proto--!>}\n\\newline\n<!--desc--!>\n";

	public static void main(String args[]) throws Exception
	{
		String latexFile = "";

		if (args.length < 2)
			throw new IllegalArgumentException("must have at least 2 arguments--outFile and one input");

		String outFile = args[0];
		for (int i=1; i<args.length; i++)
		{
			String fileName = args[i];

			File file = new File(fileName);
			LatexMaker latex = new LatexMaker(file);
			latexFile += latex.parse(latex_template);
		}

		PrintStream out = new PrintStream(new FileOutputStream(new File(outFile)));
		out.println(latexFile);
	}
}
