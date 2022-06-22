#!/bin/bash

pattern="template\s*<.*(typename\s*\.\.\.\s*\w*).*>\s*void\s+schedule\(.*\)\s*{"

grep -Pz "$pattern" "../../homework/schedule/schedule.hpp" > /dev/null

if [[ $? != 0 ]]; then
    echo "❌ There is no template version of schedule function"
    exit 1
fi

echo "✅ Found template version of schedule function"
