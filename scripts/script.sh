while IFS= read -r path; do
    mkdir -p "$(dirname "$path")"
    touch "$path"
done < paths.txt