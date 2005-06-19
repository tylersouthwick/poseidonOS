package org.northfuse.documentation;

import java.io.*;
import java.util.*;

public class CommentExtractor
{
	BufferedReader reader;
	boolean commentStarted;

	public CommentExtractor(BufferedReader reader)
	{
		this.reader = reader;
		commentStarted = false;
	}

	private List findNextComment() throws Exception
	{
		String line;
		List comments = new ArrayList();

		do
		{
			line = reader.readLine();
		} while ((line != null) && !(line.startsWith("/*")));

		comments.add(line);

		if (line == null)
			return null;

		if (line.endsWith("*/"))
			return findNextComment();

		String newLine;
		do
		{
			newLine = reader.readLine();

			if (newLine == null)
				throw new IllegalStateException("comment block didn't end!");

			comments.add(newLine);
		} while (!newLine.endsWith("*/"));

		return comments;
	}

	public String getNextComment() throws Exception
	{
		String block = "";

		List comments = findNextComment();
		if (comments == null)
			return null;

		Iterator itr = comments.iterator();
		while (itr.hasNext())
		{
			String line = (String)itr.next();
			if (line.startsWith("/*")) continue;
			if (line.endsWith("*/")) continue;

			int starts = line.indexOf("*");

			block += line.substring(starts + 1, line.length()).trim() + "\n";
		}

		return block;
	}
}
