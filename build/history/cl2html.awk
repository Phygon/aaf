#
# Generate an html table from a change log (output of cvs2cl.pl)
#
# $ cat ChangeLog | awk -f build/history/cl2html.awk > changelog.html
#
# Tim Bingham
#
BEGIN {
  entrytext = "";
  printHeader();
}

/^[0-9]+-[0-9]+-[0-9]+/ {
  if (entrytext != "") {
    entry(entrytext);
  }
  /* Build new table row */
  date = $1;
  gsub("-", "/", date);
  name = $3;
  entrytext = "";
  files = "";
  comments = "";
}

/^\t/ {
  /* Accumulate the text of this entry */
  entrytext = entrytext $0;
}

END {
  if (entrytext) {
    entry(entrytext);
  }
  printTrailer();
}

function printHeader() {
  printf("\
<!-- This file was generated by cl2html.awk -->\n\
<!-- If you edit this file your changes may be lost. -->\n\
<!-- -->\n\
<TABLE>\n");
  printf("\
<TR>\n\
  <TH>Date</TH>\n\
  <TH>Developer</TH>\n\
  <TH>Files</TH>\n\
  <TH>Checkin comment</TH>\n\
</TR>\n");
}

function printRow(date, name, files, comments, color) {
  printf("\
<TR>\n\
  <TD>%s</TD>\n\
  <TD bgcolor=\"%s\">%s</TD>\n\
  <TD bgcolor=\"%s\">%s</TD>\n\
  <TD bgcolor=\"%s\">%s</TD>\n\
</TR>\n",
    date, color, name, color, files, color, comments);
}

function printTrailer() {
  printf("</TABLE>\n");
}

# Remove first n characters of s
function trim(s, n) {
  return substr(s, n + 1, length(s) - n);
}

function rowcolor(files) {
  result = "#FFCCCC";
  /* Get first file */
  split(files, fns, ",");
  ff = fns[1];
  printf("<!--[%s]-->\n", ff);
  /* Get directory of file */
  if (match(ff, "ref-impl/src/OM")) {
    result = "#CCFFCC";
  } else if (match(ff, "ref-impl/include/OM")) {
    result = "#CCFFCC";
  }
  return result;
}

function entry(entrytext) {
#  printf("<!--[%s]-->\n", entrytext);
  gsub("\t", " ", entrytext);
  entrytext = trim(entrytext, 3);
  f = split(entrytext, fields, ":");
#  printf("<!--[%d]-->\n", f);
#  for (i = 1; i <= f; i++) {
#    printf("<!--[%d : \"%s\"]-->\n", i, fields[i]);
#  }
  /* We should have at least a file name and a comment */
  if (f < 2) {
    printf("cl2html : Error near \"%s\"\n", entrytext) | "cat 1>&2";
    exit(1);
  }
  if (match(fields[1], "/$")) {
    /* The first field is a directory */
    dir = fields[1];
    files = trim(fields[2], 1);
    gsub(" ", "", files);
    n = split(files, names, ",");
#    printf("<!--[%d]-->\n", n);
#    for (i = 1; i <= n; i++) {
#      printf("<!--[%d : \"%s\"]-->\n", i, names[i]);
#    }
    /* Insert directory names */
    files = dir names[1];
    for (i = 2; i <= n; i++) {
      files = files ", " dir names[i];
    }
    cs = 3; /* Start of comment */
  } else {
    /* The first field is not a directory */
    dir = "";
    files = fields[1];
    cs = 2; /* Start of comment */
  }
  /* Put comment back together - undo split on ":" */
  comments = trim(fields[cs], 1);
  for (i = cs + 1; i <= f; i++) {
    comments = comments ":" fields[i]
  }

  color = rowcolor(files);

#  printf("<!--[dir      = \"%s\"]-->\n", dir);
#  printf("<!--[files    = \"%s\"]-->\n", files);
#  printf("<!--[comments = \"%s\"]-->\n", comments);
  /* Print previous table row */
  printRow(date, name, files, comments, color);
}
