package org.northfuse.documentation;

import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class LatexMaker
{
	CommentExtractor comments; 
	BufferedReader reader;

	public LatexMaker(File fileName) throws Exception
	{
		reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)));
	}

	private String strip(String pattern, String string)
	{
		return string.substring(pattern.length() + 1, string.length());
	}

	public String parse(String latex_template) throws Exception
	{
		Set docs = getDocs(reader);
		Iterator itr = docs.iterator();
		String latex_docs = "";

		while (itr.hasNext())
		{
			Map map = (Map)itr.next();
			String temp_tex = latex_template;
			Iterator map_itr = map.keySet().iterator();

			while (map_itr.hasNext())
			{
				String key = (String)map_itr.next();
				String value = (String) map.get(key);
				try
				{
					Pattern p = Pattern.compile("<!--" + key + "--!>");
					Matcher m = p.matcher(temp_tex);
					temp_tex = m.replaceAll(value);
				} catch (PatternSyntaxException e) { System.err.println(e);}
			}

			latex_docs += temp_tex;
		}

		return latex_docs;
	}

	public Set getDocs(BufferedReader reader) throws Exception
	{
		comments = new CommentExtractor(reader);
		Set docs = new HashSet();

		String block;
		while ((block = comments.getNextComment()) != null)
		{
			String[] lines = block.split("\n");
			if (lines[0].equals("\\do_latex"))
			{
				Map tokens = new HashMap();

				for (int i=1; i<lines.length; i++)
				{

					if (lines[i].startsWith("\\name")) 
						tokens.put("name", strip("\\name", lines[i]));
					if (lines[i].startsWith("\\desc")) 
					{
						String desc = "";
						if (tokens.get("desc") != null)
							desc = (String)tokens.get("desc");
						desc += strip("\\desc", lines[i]) + " ";
						tokens.put("desc", desc);
					}
					if (lines[i].startsWith("\\date")) 
						tokens.put("date", strip("\\date", lines[i]));
					if (lines[i].startsWith("\\proto")) 
						tokens.put("proto", strip("\\proto", lines[i]));
				}

				docs.add(tokens);
			}
		}

		return docs;
	}
}
