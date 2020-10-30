%  File   : XRFDEF.PL%  Author : Dave Bowen%  Updated: 6/10/86%  Purpose: Handles .DEFinition files for XREF.%----------------------------------------------------------------------%declarations%:- module(xrfdef, [check_filename/1,                   check_width/1,		   is_system/1,		   load/1,		   load_list/1,		   load_file/1]).:- use_module(xrf, [crecord/2,                    mark_interpreted/1]).:- use_module(xrftty, [see_chek/1,		   expand_file_name/2		]).:- use_module(library(basics), [	member/2   ]).%end%% ----------------------------------------------------------------------/*-----------------------------------------------------------------------------Data for user definitions.The following terms may be recorded using a predicate as the key:	$system		for "built-in" predicates without			    predicate_property(P, built_in)			    (Escape hatch; should not be any such.)	$system_used	for built-in predicates to be xref-ed anyway.	$known(I,M)	for predicates known to be defined in module M, file I	$applies(M:P,T)	for predicates P which apply one of their arguments T.			    M is the module in which P is defined.	$called		for predicates which are called from other placesThe following types of term may be recorded under the key $define:	width(N)	where N is the required page width for the 			cross-reference listing.	title(X)	where X is the title for the listing.	cross_ref_file(F) where F is the filename for the listing.	globals_file(G)	where G is the filename for the listing of the imports			and exports of each file. If G='no' then no such 			listing will be produced.	update_module_declarations(YesOrNo) where YesOrNo must be 'yes' or			'no'.  If it is 'yes' each file referenced will have			its 'module' and 'use_module' statements updated			(these must be in a particular format -			 see below).-----------------------------------------------------------------------------*/				% Load in definition file containing system				% or known predicates, or operators.load([F|L]) :- !,	load(F),	load(L).load([]) :- !.load(File1) :-        expand_file_name(File1,File),	see_chek(File),	!,	load_file(File),	seen.load(_).			% if see_chek failed.				% Load given DEFinition file.load_file(File) :-	repeat,	    read(T),	    (   T = end_of_file	    ;   note(T), fail	    ),	!,	write('Definition file '), write(File), write(' loaded'), nl.				% Load List as though terms of DEFinition file.load_list(List) :-	member(T, List),	note(T),	fail.load_list(_List).				% Process terms in definition file.note((H :- B)) :- !,	call(B),	note(H).note(system(P)) :-	get_pred_spec(P, S), !,	crecord(S, '$system').	% Treat P as a system (built-in) predicate,				% not known by predicate_property.note(system_used(P)) :-	get_pred_spec(P, S), !,	crecord(S, '$system_used').	% P is a system (built-in) predicate,					% but xref it anyway.note(known(P,I)) :-	get_pred_spec(P, S), !,	crecord(S, '$known'(I,'???')).	% P is known to be defined in file Inote(known(P,I,M)) :-	get_pred_spec(P, S), !,	crecord(S, '$known'(I,M)).	% P known defined in module M, file Inote(op(Prec,Assoc,Name)) :- !,	op(Prec, Assoc, Name).		% operator defns handled as normally				% BEWARE; get_pred_spec NOT called on applies!note(applies(M:P,T)) :- !,	recorda(P, '$applies'(M:P,T), _).    % P must contain T which it Callsnote(applies(P,T)) :-	\+ P = _:_, !,	recorda(P, '$applies'(_M:P,T), _).   % P must contain T which it Callsnote(called(P)) :-	get_pred_spec(P, S), !,	mark_interpreted(S).		% P is called from somewhere%  The following clauses deal with answers to questions about the layout%  of output, what files to use, and so on, which the user would otherwise%  have to type in.note(width(N)) :- !,	check_width(N),			% Paper width for cross-ref listing	recorda('$define', width(N), _).note(title(T)) :- !,			% Title of cross-ref listing	recorda('$define', title(T), _).note(cross_ref_file(F)) :- !, 		% File name for cross-ref listing	check_filename(F),	recorda('$define', cross_ref_file(F), _). note(globals_file(G)) :- !,		% File name for imports/exports listing	check_filename(G),		% - may be 'no' meaning no listing reqd	recorda('$define', globals_file(G), _).note(update_module_declarations(Yes_or_No)) :- !,	% If imports/exports 	check_yesorno(Yes_or_No),	     % listed, do you want your files 	recorda('$define', update_module_declarations(Yes_or_No), _). % updatednote(Botched) :-	write('! Unrecognisable definition '),	write(Botched), write(' -- ignored.'), nl.% Routines for checking validity of arguments %   get_pred_spec lets the user specify a predicate either by giving a%   most general term (which is what XREF has always wanted in the past)%   or by giving a Functor/Arity pair (which is more consistent with the%   other things that want to know about predicates).  If the specifier%   is not recognisable, get_pred_spec fails so that note/1 can report it.get_pred_spec(Functor/Arity, MGT) :-	atom(Functor),	integer(Arity),	Arity >= 0,	!,	functor(MGT, Functor, Arity).get_pred_spec(Term, MGT) :-	nonvar(Term),	functor(Term, Functor, Arity),	atom(Functor),	% don't accept known(17) !	!,	functor(MGT, Functor, Arity).				/* Check Width is in range */check_width(Width) :-  	integer(Width), Width >= 50, Width =< 150, !.check_width(Width) :-	write('! Width ('), write(Width),	write(') should be between 50 and 150.'), nl,	fail.				/* Check legal file name */check_filename(F) :-	atom(F), !.check_filename(F) :-	write('! File name ('), write(F),	write(') ill-formed.'), nl,	fail.				/* Check for yes/no */check_yesorno(Y_or_N) :-	(  Y_or_N == yes ; Y_or_N == no  ), !.check_yesorno(Y_or_N) :-	write('! Flag ('), write(Y_or_N),	write(') should be ''yes'' or ''no''.'), nl,	fail.is_system(P) :-	predicate_property(P, built_in),	\+ recorded(P, '$system_used', _).is_system(P) :-	\+ predicate_property(P, built_in),	recorded(P, '$system', _).