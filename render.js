import { marked } from "https://cdn.jsdelivr.net/npm/marked/lib/marked.esm.js";
import DOMPurify from "https://cdn.jsdelivr.net/npm/dompurify/dist/purify.min.js";

async function renderMarkdown() {
    const markdownBlocks = document.querySelectorAll(".markdown");

    for (const block of markdownBlocks) {
        const raw = block.innerText || "";
        const unsafeHtml = await marked.parse(raw);
        block.innerHTML = DOMPurify.sanitize(unsafeHtml);
    }

    if (window.MathJax) {
        window.MathJax.typesetPromise();
    } else {
        window.addEventListener("load", () => {
            if (window.MathJax) window.MathJax.typesetPromise();
        });
    }
}

window.addEventListener("DOMContentLoaded", renderMarkdown);
