# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.multitexture.Debug:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/Debug/multitexture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/Debug/multitexture


PostBuild.multitexture.Release:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/Release/multitexture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/Release/multitexture


PostBuild.multitexture.MinSizeRel:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/MinSizeRel/multitexture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/MinSizeRel/multitexture


PostBuild.multitexture.RelWithDebInfo:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/RelWithDebInfo/multitexture:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_9/multitexture/RelWithDebInfo/multitexture




# For each target create a dummy ruleso the target does not have to exist
